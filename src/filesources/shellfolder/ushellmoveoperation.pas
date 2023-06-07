unit uShellMoveOperation;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils,
  Windows, ShlObj, ComObj, ActiveX,
  uFileSourceOperation,
  uFileSourceMoveOperation,
  uFileSource,
  uFile,
  uShellFileSource,
  uShellFileOperation,
  uShellFileSourceUtil;

type

  { TShellMoveOperation }

  TShellMoveOperation = class(TFileSourceMoveOperation)

  protected
    FFileOp: IFileOperation;
    FTargetFolder: IShellItem;
    FSourceFilesTree: TItemList;
    FShellFileSource: IShellFileSource;
    FStatistics: TFileSourceMoveOperationStatistics;

    procedure ShowError(const sMessage: String);
  public
    constructor Create(aFileSource: IFileSource;
                       var theSourceFiles: TFiles;
                       aTargetPath: String); virtual reintroduce;

    destructor Destroy; override;

    procedure Initialize; override;
    procedure MainExecute; override;
    procedure Finalize; override;

  end;

implementation

uses
  uFileSourceOperationOptions, uFileSourceOperationUI, uShellFolder, uGlobs,
  uLog, uLng;

procedure TShellMoveOperation.ShowError(const sMessage: String);
begin
  if (log_errors in gLogOptions) then
  begin
    logWrite(Thread, sMessage, lmtError);
  end;

  if AskQuestion(sMessage, '', [fsourSkip, fsourAbort],
                 fsourSkip, fsourAbort) = fsourAbort then
  begin
    RaiseAbortOperation;
  end;
end;

constructor TShellMoveOperation.Create(aFileSource: IFileSource;
  var theSourceFiles: TFiles; aTargetPath: String);
begin
  FShellFileSource:= aFileSource as IShellFileSource;
  FFileOp:= CreateComObject(CLSID_FileOperation) as IFileOperation;
  inherited Create(aFileSource, theSourceFiles, aTargetPath);
end;

destructor TShellMoveOperation.Destroy;
begin
  inherited Destroy;
  FreeAndNil(FSourceFilesTree);
end;

procedure TShellMoveOperation.Initialize;
var
  AName: String;
  Index: Integer;
  AObject: PItemIDList;
  AFolder: IShellFolder2;
begin
  FStatistics := RetrieveStatistics;

  FSourceFilesTree:= TItemList.Create;
  try
    for Index := 0 to SourceFiles.Count - 1 do
    begin
      AName:= SourceFiles[Index].LinkProperty.LinkTo;
      OleCheck(FShellFileSource.ParseDisplayName(AName, AObject));
      FSourceFilesTree.Add(AObject);
    end;
    OleCheck(FShellFileSource.FindFolder(TargetPath, AFolder));
    OleCheck(SHGetIDListFromObject(AFolder, AObject));
    try
      OleCheck(SHCreateItemFromIDList(AObject, IShellItem, FTargetFolder));
    finally
      CoTaskMemFree(AObject);
    end;
  except
    on E: Exception do ShowError(E.Message);
  end;
end;

procedure TShellMoveOperation.MainExecute;
var
  dwCookie: DWORD;
  siItemArray: IShellItemArray;
  ASink: TFileOperationProgressSink;
begin
  ASink:= TFileOperationProgressSink.Create(@FStatistics, @UpdateStatistics);

  FFileOp.SetOperationFlags(FOF_SILENT or FOF_NOCONFIRMMKDIR);

  try
    FFileOp.Advise(ASink, @dwCookie);
    try
      OleCheck(SHCreateShellItemArrayFromIDLists(FSourceFilesTree.Count, PPItemIDList(FSourceFilesTree.List), siItemArray));
      OleCheck(FFileOp.MoveItems(siItemArray, FTargetFolder));
      OleCheck(FFileOp.PerformOperations);
    finally
      FFileOp.Unadvise(dwCookie);
    end;
  except
    on E: Exception do ShowError(E.Message);
  end;
end;

procedure TShellMoveOperation.Finalize;
begin

end;

end.

