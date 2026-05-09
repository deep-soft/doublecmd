var
  viewerImageItemsIdentifiers: TStringArray = (
    'ViewerForm.ZoomIn',
    'ViewerForm.ZoomOut',
    'NSToolbarFlexibleSpaceItem',
    'ViewerForm.Rotate270',
    'ViewerForm.Rotate90',
    'ViewerForm.Mirror',
    'NSToolbarFlexibleSpaceItem',

    'ViewerForm.GifMove',
    'ViewerForm.GifPrev',
    'ViewerForm.GifNext',
    'ViewerForm.GifExport',
    'NSToolbarFlexibleSpaceItem',

    'ViewerForm.HighLight',
    'ViewerForm.Crop',
    'ViewerForm.RedEyes',
    'NSToolbarFlexibleSpaceItem',

    'ViewerForm.Paint',
    'ViewerForm.PenMode',
    'ViewerForm.PenWidth',
    'ViewerForm.PenColor',

    'NSToolbarFlexibleSpaceItem',
    'ViewerForm.Resize',
    'ViewerForm.Slide'
  );

type

  { TCocoaViewerFormHandler }

  TCocoaViewerFormHandler = class( TViewerFormHandler )
    procedure onShowModeChanged(
      const viewer: TfrmViewer;
      const mode: TViewerShowMode ); override;
    procedure onGifStateChanged(
      const viewer: TfrmViewer;
      const states: TViewerGifStates ); override;
    procedure onImageEditStateChanged(
      const viewer: TfrmViewer ); override;
    procedure onSlideStateChanged(
      const viewer: TfrmViewer ); override;

    procedure onPenWidthChanged( Sender: TObject );
    procedure onSlideStart( Sender: TObject );
  end;

function getCurrentViewerForm: TfrmViewer;
var
  form: TCustomForm;
begin
  Result:= nil;
  form:= Screen.ActiveCustomForm;
  if form is TfrmViewer then
    Result:= TfrmViewer(form);
end;

procedure viewerAttachImageToolBar( const form: TCustomForm );
var
  toolBar: NSToolBar;
  i: Integer;
begin
  toolBar:= TCocoaToolBarUtils.getToolBar( form );
  if toolBar = nil then
    Exit;

  if TCocoaToolBarUtils.findItemIndexByIdentifier(toolBar,viewerImageItemsIdentifiers[0]) > 0 then
    Exit;

  for i:= 0 to Length(viewerImageItemsIdentifiers)-1 do
    TCocoaToolBarUtils.addItemWithIdentifier( toolBar, viewerImageItemsIdentifiers[i] );
end;

procedure viewerDeattachImageToolBar( const form: TCustomForm );
var
  toolBar: NSToolBar;
  index: Integer;
  i: Integer;
begin
  toolBar:= TCocoaToolBarUtils.getToolBar( form );
  if toolBar = nil then
    Exit;

  index:= TCocoaToolBarUtils.findItemIndexByIdentifier( toolBar, viewerImageItemsIdentifiers[0] );
  if index < 0 then
    Exit;

  for i:= toolBar.items.count-1 downto index do
    TCocoaToolBarUtils.removeItemByIndex( toolBar, i );
end;

procedure viewerReloadAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_Reload( [] );
end;

procedure viewerPrevAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_LoadPrevFile( [] );
end;

procedure viewerNextAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_LoadNextFile( [] );
end;

procedure viewerCopyAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_CopyFile( [] );
end;

procedure viewerMoveAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_MoveFile( [] );
end;

procedure viewerDeleteAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_DeleteFile( [] );
end;

procedure viewerZoomInAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_ZoomIn( [] );
end;

procedure viewerZoomOutAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_ZoomOut( [] );
end;

procedure viewerRotate270Action( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_Rotate270( [] );
end;

procedure viewerRotate90Action( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_Rotate90( [] );
end;

procedure viewerMirrorAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.cm_MirrorHorz( [] );
end;

procedure viewerGifMoveAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.btnGifMoveClick( nil );
end;

procedure viewerGifPrevAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.btnPrevGifFrameClick( nil );
end;

procedure viewerGifNextAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.btnNextGifFrameClick( nil );
end;

procedure viewerGifExportAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.btnGifToBmpClick( nil );
end;

procedure viewerHighlightAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then begin
    form.btnHightlight.Down:= NOT form.btnHightlight.Down;
    form.btnPaintHightlight( form.btnHightlight );
  end;
end;

procedure viewerCropAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.btnCutTuImageClick( nil );
end;

procedure viewerRedEyesAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.btnRedEyeClick( nil );
end;

procedure viewerPaintAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then begin
    form.btnPaint.Down:= NOT form.btnPaint.Down;
    form.btnPaintHightlight( form.btnPaint );
  end;
end;

procedure viewerPenModeAction( const Sender: id );
var
  form: TfrmViewer;
  menuItem: TMenuItem = nil;
  penModeItem: NSToolBarItemGroup absolute Sender;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then begin
    case penModeItem.selectedIndex of
      0: menuItem:= form.miPen;
      1: menuItem:= form.miRect;
      2: menuItem:= form.miEllipse;
    end;

    if Assigned(menuItem) then
      form.miPenClick( menuItem );
  end;
end;

procedure viewerPenColorAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.btnPenColor.Click;
end;

procedure viewerResizeAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.btnResizeClick( nil );
end;

procedure viewerSlideAction( const Sender: id );
var
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then
    form.btnSlideShowClick( nil );
end;

procedure onViewerGetPenWidthMenu( const menu: TMenu );
var
  i: Integer;
  item: TMenuItem;
begin
  for i:= 1 to 25 do begin
    item:= TMenuItem.Create( menu );
    item.Caption:= i.ToString;
    item.Tag:= i;
    item.OnClick:= @TCocoaViewerFormHandler(viewerFormHandler).onPenWidthChanged;
    menu.Items.Add( item );
  end;
end;

procedure onViewerGetSlideMenu( const menu: TMenu );
var
  i: Integer;
  item: TMenuItem;
begin
  for i:= 1 to 25 do begin
    item:= TMenuItem.Create( menu );
    item.Caption:= i.ToString;
    item.Tag:= i;
    item.OnClick:= @TCocoaViewerFormHandler(viewerFormHandler).onSlideStart;
    menu.Items.Add( item );
  end;
end;

const
  viewerReloadItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Reload';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'arrow.clockwise';
    title: 'Reload';
    tips: 'Reload';
    bordered: True;
    onAction: @viewerReloadAction;
  );

  viewerPrevItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Prev';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'chevron.left';
    title: 'Prev';
    tips: 'Prev';
    bordered: True;
    onAction: @viewerPrevAction;
  );

  viewerNextItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Next';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'chevron.right';
    title: 'Next';
    tips: 'Next';
    bordered: True;
    onAction: @viewerNextAction;
  );

  viewerCopyFileItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.CopyFile';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'doc.on.doc';
    title: 'CopyFile';
    tips: 'CopyFile';
    bordered: True;
    onAction: @viewerCopyAction;
  );

  viewerMoveFileItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.MoveFile';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'scissors';
    title: 'MoveFile';
    tips: 'MoveFile';
    bordered: True;
    onAction: @viewerMoveAction;
  );

  viewerDeleteFileItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.DeleteFile';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'trash';
    title: 'DeleteFile';
    tips: 'DeleteFile';
    bordered: True;
    onAction: @viewerDeleteAction;
  );


  viewerZoomInItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.ZoomIn';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'plus.magnifyingglass';
    title: 'Zoom In';
    tips: 'Zoom In';
    bordered: True;
    onAction: @viewerZoomInAction;
  );

  viewerZoomOutItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.ZoomOut';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'minus.magnifyingglass';
    title: 'Zoom Out';
    tips: 'Zoom Out';
    bordered: True;
    onAction: @viewerZoomOutAction;
  );

  viewerRotate270ItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Rotate270';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'rotate.left';
    title: 'Rotate -90 degree';
    tips: 'Rotate -90 degree';
    bordered: True;
    onAction: @viewerRotate270Action;
  );

  viewerRotate90ItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Rotate90';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'rotate.right';
    title: 'Rotate +90 degree';
    tips: 'Rotate +90 degree';
    bordered: True;
    onAction: @viewerRotate90Action;
  );

  viewerMirrorItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Mirror';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'arrow.left.and.right.righttriangle.left.righttriangle.right';
    title: 'Mirror';
    tips: 'Mirror';
    bordered: True;
    onAction: @viewerMirrorAction;
  );

  viewerGifMoveItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.GifMove';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    appValidates: True;
    iconName: 'play.fill';
    title: '';
    tips: '';
    bordered: True;
    onAction: @viewerGifMoveAction;
  );

  viewerGifPrevItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.GifPrev';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    appValidates: True;
    iconName: 'arrow.left';
    title: 'GifPrev';
    tips: 'GifPrev';
    bordered: True;
    onAction: @viewerGifPrevAction;
  );

  viewerGifNextItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.GifNext';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    appValidates: True;
    iconName: 'arrow.right';
    title: 'GifNext';
    tips: 'GifNext';
    bordered: True;
    onAction: @viewerGifNextAction;
  );

  viewerGifExportItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.GifExport';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    appValidates: True;
    iconName: 'arrow.down.circle.fill';
    title: 'GifExport';
    tips: 'GifExport';
    bordered: True;
    onAction: @viewerGifExportAction;
  );

  viewerHighLightItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.HighLight';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    appValidates: True;
    iconName: 'paintbrush.pointed';
    title: 'Highlight';
    tips: 'Highlight';
    bordered: True;
    onAction: @viewerHighlightAction;
  );

  viewerCropItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Crop';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    appValidates: True;
    iconName: 'crop';
    title: 'Crop';
    tips: 'Crop';
    bordered: True;
    onAction: @viewerCropAction;
  );

  viewerRedEyesItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.RedEyes';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    appValidates: True;
    iconName: 'eye';
    title: 'Red Eyes';
    tips: 'Red Eyes';
    bordered: True;
    onAction: @viewerRedEyesAction;
  );

  viewerPaintItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Paint';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'pencil';
    title: 'Paint';
    tips: 'Paint';
    bordered: True;
    onAction: @viewerPaintAction;
  );


  viewerPenModePenItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.PenMode.Pen';
    iconName: 'scribble';
    title: 'Pen';
    tips: 'Pen';
    bordered: True;
    onAction: nil;
  );

  viewerPenModeRectItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.PenMode.Rect';
    iconName: 'rectangle';
    title: 'Rect';
    tips: 'Rect';
    bordered: True;
    onAction: nil;
  );

  viewerPenModeEllipseItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.PenMode.Ellipse';
    iconName: 'oval';
    title: 'Ellipse';
    tips: 'Ellipse';
    bordered: True;
    onAction: nil;
  );

  viewerPenModeItemConfig: TCocoaConfigToolBarItemGroup = (
    identifier: 'ViewerForm.PenMode';
    priority: NSToolbarItemVisibilityPriorityLow;
    navigational: False;
    iconName: '';
    title: '';
    tips: '';
    bordered: True;
    onAction: @viewerPenModeAction;

    representation: NSToolbarItemGroupControlRepresentationCollapsed;
    selectionMode: NSToolbarItemGroupSelectionModeSelectOne;
    selectedIndex: 0;
    subitems: (
    );
  );

  viewerPenWidthItemConfig: TCocoaConfigToolBarItemMenu = (
    identifier: 'ViewerForm.PenWidth';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'lineweight';
    title: 'Width';
    tips: '';
    bordered: True;
    onAction: nil;

    showsIndicator: False;
    menu: nil;
    onGetMenu: @onViewerGetPenWidthMenu;
  );

  viewerPenColorItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.PenColor';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    appValidates: True;
    iconName: 'eyedropper';
    title: 'Color';
    tips: '';
    bordered: True;
    onAction: @viewerPenColorAction;
  );

  viewerResizeItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Resize';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'rectangle.on.rectangle';
    title: 'Resize';
    tips: 'Resize';
    bordered: True;
    onAction: @viewerResizeAction;
  );

  viewerSlideItemConfig: TCocoaConfigToolBarItemMenu = (
    identifier: 'ViewerForm.Slide';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'play';
    title: 'Slide Show';
    tips: 'Slide Show';
    bordered: True;
    onAction: @viewerSlideAction;

    showsIndicator: True;
    menu: nil;
    onGetMenu: @onViewerGetSlideMenu;
  );

  viewerFormConfig: TCocoaConfigForm = (
    name: '';
    className: 'TfrmViewer';
    isMainForm: False;

    titleBar: (
      transparent: False;
      separatorStyle: NSTitlebarSeparatorStyleAutomatic;
    );

    toolBar: (
      identifier: 'ViewerForm.ToolBar';
      style: NSWindowToolbarStyleUnifiedCompact;
      displayMode: NSToolbarDisplayModeIconOnly;
      autoHideInFullScreen: True;

      allowsUserCustomization: False;
      autosavesConfiguration: False;

      items: (
      );
      defaultItemsIdentifiers: (
        'ViewerForm.Reload',
        'ViewerForm.Prev',
        'ViewerForm.Next',
        'ViewerForm.CopyFile',
        'ViewerForm.MoveFile',
        'ViewerForm.DeleteFile'
      );
      allowedItemsIdentifiers: (
        'ViewerForm.Reload',
        'ViewerForm.Prev',
        'ViewerForm.Next',
        'ViewerForm.CopyFile',
        'ViewerForm.MoveFile',
        'ViewerForm.DeleteFile',

        'ViewerForm.ZoomIn',
        'ViewerForm.ZoomOut',
        'ViewerForm.Rotate270',
        'ViewerForm.Rotate90',
        'ViewerForm.Mirror',

        'ViewerForm.GifMove',
        'ViewerForm.GifPrev',
        'ViewerForm.GifNext',
        'ViewerForm.GifExport',

        'ViewerForm.HighLight',
        'ViewerForm.Crop',
        'ViewerForm.RedEyes',
        'ViewerForm.Paint',
        'ViewerForm.PenMode',
        'ViewerForm.PenWidth',
        'ViewerForm.PenColor',
        'ViewerForm.Resize',
        'ViewerForm.Slide'
      );
      itemCreator: nil;      // default item Creator
    );
  );

procedure doInitViewerFormConfig;
begin
  viewerPenModeItemConfig.subitems:= [
    TCocoaToolBarUtils.toClass(viewerPenModePenItemConfig),
    TCocoaToolBarUtils.toClass(viewerPenModeRectItemConfig),
    TCocoaToolBarUtils.toClass(viewerPenModeEllipseItemConfig)
  ];

  viewerFormConfig.toolBar.items:= [
    TCocoaToolBarUtils.toClass(viewerReloadItemConfig),
    TCocoaToolBarUtils.toClass(viewerPrevItemConfig),
    TCocoaToolBarUtils.toClass(viewerNextItemConfig),
    TCocoaToolBarUtils.toClass(viewerCopyFileItemConfig),
    TCocoaToolBarUtils.toClass(viewerMoveFileItemConfig),
    TCocoaToolBarUtils.toClass(viewerDeleteFileItemConfig),

    TCocoaToolBarUtils.toClass(viewerZoomInItemConfig),
    TCocoaToolBarUtils.toClass(viewerZoomOutItemConfig),
    TCocoaToolBarUtils.toClass(viewerRotate270ItemConfig),
    TCocoaToolBarUtils.toClass(viewerRotate90ItemConfig),
    TCocoaToolBarUtils.toClass(viewerMirrorItemConfig),

    TCocoaToolBarUtils.toClass(viewerGifMoveItemConfig),
    TCocoaToolBarUtils.toClass(viewerGifPrevItemConfig),
    TCocoaToolBarUtils.toClass(viewerGifNextItemConfig),
    TCocoaToolBarUtils.toClass(viewerGifExportItemConfig),

    TCocoaToolBarUtils.toClass(viewerHighLightItemConfig),
    TCocoaToolBarUtils.toClass(viewerCropItemConfig),
    TCocoaToolBarUtils.toClass(viewerRedEyesItemConfig),

    TCocoaToolBarUtils.toClass(viewerPaintItemConfig),
    TCocoaToolBarUtils.toClass(viewerPenModeItemConfig),
    TCocoaToolBarUtils.toClass(viewerPenWidthItemConfig),
    TCocoaToolBarUtils.toClass(viewerPenColorItemConfig),
    TCocoaToolBarUtils.toClass(viewerResizeItemConfig),
    TCocoaToolBarUtils.toClass(viewerSlideItemConfig)
  ];

  FreeAndNil( viewerFormHandler );
  viewerFormHandler:= TCocoaViewerFormHandler.Create;
end;

{ TCocoaViewerFormHandler }

procedure TCocoaViewerFormHandler.onShowModeChanged(
  const viewer: TfrmViewer;
  const mode: TViewerShowMode );
begin
  if mode = vsmImage then
    viewerAttachImageToolBar( viewer )
  else
    viewerDeattachImageToolBar( viewer )
end;

procedure TCocoaViewerFormHandler.onGifStateChanged(
  const viewer: TfrmViewer;
  const states: TViewerGifStates);
var
  moveEnabled: Boolean;
  prevEnabled: Boolean;
  nextEnabled: Boolean;
  exportEnabled: Boolean;

  toolBar: NSToolBar;
  item: NSToolBarItem;

  moveImageName: String;
  moveImage: NSImage;
begin
  if vgsIsGif in states then begin
    moveEnabled:= True;
    prevEnabled:= vgsPrevFrame in states;
    nextEnabled:= vgsNextFrame in states;
    exportEnabled:= True;
  end else begin
    moveEnabled:= False;
    prevEnabled:= False;
    nextEnabled:= False;
    exportEnabled:= False;
  end;

  viewerAttachImageToolBar( viewer );
  toolBar:= TCocoaToolBarUtils.getToolBar( viewer );
  if toolBar = nil then
    Exit;

  item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.GifMove');
  item.setEnabled( moveEnabled );
  if vgsPlaying in states then
    moveImageName:= 'pause.fill'
  else
    moveImageName:= 'play.fill';
  moveImage:= NSImage.imageWithSystemSymbolName_accessibilityDescription(
    StringToNSString(moveImageName), nil );
  item.setImage( moveImage );

  item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.GifPrev');
  item.setEnabled( prevEnabled );
  item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.GifNext');
  item.setEnabled( nextEnabled );
  item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.GifExport');
  item.setEnabled( exportEnabled );
end;

procedure TCocoaViewerFormHandler.onImageEditStateChanged(
  const viewer: TfrmViewer );
var
  toolBar: NSToolBar;
  item: NSToolBarItem;

  procedure updateHighlightState;
  var
    highlightButton: TToolButton;
    highlightImageName: String;
    highlightImage: NSImage;
  begin
    highlightButton:= viewer.btnHightlight;
    item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.HighLight');
    item.setEnabled( highlightButton.Enabled );
    if highlightButton.Down then
      highlightImageName:= 'paintbrush.pointed.fill'
    else
      highlightImageName:= 'paintbrush.pointed';
    highlightImage:= NSImage.imageWithSystemSymbolName_accessibilityDescription(
      StringToNSString(highlightImageName), nil );
    item.setImage( highlightImage );

    item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.Crop');
    item.setEnabled( highlightButton.Down );
    item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.RedEyes');
    item.setEnabled( highlightButton.Down );
  end;

  procedure updatePaintState;
  var
    paintButton: TToolButton;
    paintImageName: String;
    paintImage: NSImage;
  begin
    paintButton:= viewer.btnPaint;
    item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.Paint');
    item.setEnabled( paintButton.Enabled );
    if paintButton.Down then
      paintImageName:= 'highlighter'
    else
      paintImageName:= 'pencil';
    paintImage:= NSImage.imageWithSystemSymbolName_accessibilityDescription(
      StringToNSString(paintImageName), nil );
    item.setImage( paintImage );

    item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.PenMode');
    item.setEnabled( paintButton.Down );
    NSToolbarItemGroup(item).setSelected_atIndex( True, viewer.btnPenMode.Tag );

    item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.PenWidth');
    item.setEnabled( paintButton.Down );
    item:= TCocoaToolBarUtils.findItemByIdentifier( toolBar , 'ViewerForm.PenColor');
    item.setEnabled( paintButton.Down );
  end;

begin
  viewerAttachImageToolBar( viewer );
  toolBar:= TCocoaToolBarUtils.getToolBar( viewer );
  if toolBar = nil then
    Exit;

  updateHighlightState;
  updatePaintState;
end;

procedure TCocoaViewerFormHandler.onSlideStateChanged(const viewer: TfrmViewer);
var
  form: TfrmViewer;
  item: NSToolBarItem;
  imageName: String;
  image: NSImage;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then begin
    if form.btnSlideShow.Down then
      imageName:= 'pause'
    else
      imageName:= 'play';
    image:= NSImage.imageWithSystemSymbolName_accessibilityDescription(
      StringToNSString(imageName), nil );
    item:= TCocoaToolBarUtils.findItemByIdentifier( form, 'ViewerForm.Slide' );
    item.setImage( image );

    form.TimerViewer.Enabled:= form.btnSlideShow.Down;
  end;
end;

procedure TCocoaViewerFormHandler.onPenWidthChanged( Sender: TObject );
var
  toolBarMenuItem: TMenuItem absolute Sender;
  viewerMenuItem: TMenuItem;
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then begin
    viewerMenuItem:= form.pmPenWidth.Items[toolBarMenuItem.Tag-1];
    form.miPaintClick( viewerMenuItem );
  end;
end;

procedure TCocoaViewerFormHandler.onSlideStart( Sender: TObject );
var
  toolBarMenuItem: TMenuItem absolute Sender;
  viewerMenuItem: TMenuItem;
  form: TfrmViewer;
begin
  form:= getCurrentViewerForm;
  if Assigned(form) then begin
    viewerMenuItem:= form.pmTimeShow.Items[toolBarMenuItem.Tag-1];
    form.miPaintClick( viewerMenuItem );
    form.btnSlideShowSetState( True );
  end;
end;

