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

  TCocoaViewerFormHandler = class( TViewerFormHandler )
    procedure onShowModeChanged(
      const viewer: TfrmViewer;
      const mode: TViewerShowMode ); override;
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

procedure onViewerGetPenWidthMenu( const menu: TMenu );
var
  i: Integer;
  item: TMenuItem;
begin
  for i:= 1 to 25 do begin
    item:= TMenuItem.Create( menu );
    item.Caption:= i.ToString;
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
    onAction: nil;
  );

  viewerPrevItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Prev';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'arrow.left';
    title: 'Prev';
    tips: 'Prev';
    bordered: True;
    onAction: nil;
  );

  viewerNextItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Next';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'arrow.right';
    title: 'Next';
    tips: 'Next';
    bordered: True;
    onAction: nil;
  );

  viewerCopyFileItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.CopyFile';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'doc.on.doc';
    title: 'CopyFile';
    tips: 'CopyFile';
    bordered: True;
    onAction: nil;
  );

  viewerMoveFileItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.MoveFile';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'scissors';
    title: 'MoveFile';
    tips: 'MoveFile';
    bordered: True;
    onAction: nil;
  );

  viewerDeleteFileItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.DeleteFile';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: True;
    iconName: 'trash';
    title: 'DeleteFile';
    tips: 'DeleteFile';
    bordered: True;
    onAction: nil;
  );

  viewerZoomInItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.ZoomIn';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'plus.magnifyingglass';
    title: 'Zoom In';
    tips: 'Zoom In';
    bordered: True;
    onAction: nil;
  );

  viewerZoomOutItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.ZoomOut';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'minus.magnifyingglass';
    title: 'Zoom Out';
    tips: 'Zoom Out';
    bordered: True;
    onAction: nil;
  );

  viewerRotate270ItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Rotate270';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'rotate.left';
    title: 'Rotate -90 degree';
    tips: 'Rotate -90 degree';
    bordered: True;
    onAction: nil;
  );

  viewerRotate90ItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Rotate90';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'rotate.right';
    title: 'Rotate +90 degree';
    tips: 'Rotate +90 degree';
    bordered: True;
    onAction: nil;
  );

  viewerMirrorItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Mirror';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'arrow.left.and.right.righttriangle.left.righttriangle.right';
    title: 'Mirror';
    tips: 'Mirror';
    bordered: True;
    onAction: nil;
  );

  viewerGifMoveItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.GifMove';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'play.circle';
    title: '';
    tips: '';
    bordered: True;
    onAction: nil;
  );

  viewerGifPrevItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.GifPrev';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'arrow.left.circle';
    title: 'GifPrev';
    tips: 'GifPrev';
    bordered: True;
    onAction: nil;
  );

  viewerGifNextItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.GifNext';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'arrow.right.circle';
    title: 'GifNext';
    tips: 'GifNext';
    bordered: True;
    onAction: nil;
  );

  viewerGifExportItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.GifExport';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'arrow.down.circle';
    title: 'GifExport';
    tips: 'GifExport';
    bordered: True;
    onAction: nil;
  );

  viewerHighLightItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.HighLight';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'paintbrush.pointed.fill';
    title: 'Highlight';
    tips: 'Highlight';
    bordered: True;
    onAction: nil;
  );

  viewerCropItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Crop';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'crop';
    title: 'Crop';
    tips: 'Crop';
    bordered: True;
    onAction: nil;
  );

  viewerRedEyesItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.RedEyes';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'eye';
    title: 'Red Eyes';
    tips: 'Red Eyes';
    bordered: True;
    onAction: nil;
  );

  viewerPaintItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Paint';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'highlighter';
    title: 'Paint';
    tips: 'Paint';
    bordered: True;
    onAction: nil;
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
    onAction: nil;

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
    iconName: 'eyedropper';
    title: 'Color';
    tips: '';
    bordered: True;
    onAction: nil;
  );

  viewerResizeItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Resize';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'rectangle.on.rectangle';
    title: 'Resize';
    tips: 'Resize';
    bordered: True;
    onAction: nil;
  );

  viewerSlideItemConfig: TCocoaConfigToolBarItem = (
    identifier: 'ViewerForm.Slide';
    priority: NSToolbarItemVisibilityPriorityStandard;
    navigational: False;
    iconName: 'play';
    title: 'Slide Show';
    tips: 'Slide Show';
    bordered: True;
    onAction: nil;
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

