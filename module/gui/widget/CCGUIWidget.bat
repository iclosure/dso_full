@ECHO OFF

ECHO CCGUIWidget.BAT:     Compiling GUI\Widget

CALL CC BUTTON
CALL CC BUTTON__SetBitmapObj
CALL CC BUTTON_Bitmap
CALL CC BUTTON_BMP
CALL CC BUTTON_Create
CALL CC BUTTON_CreateIndirect
CALL CC BUTTON_Default
CALL CC BUTTON_Get
CALL CC BUTTON_GetBitmap
CALL CC BUTTON_IsPressed
CALL CC BUTTON_SelfDraw
CALL CC BUTTON_SetFocusColor
CALL CC BUTTON_SetTextAlign
CALL CC BUTTON_StreamedBitmap
CALL CC CHECKBOX
CALL CC CHECKBOX_Create
CALL CC CHECKBOX_CreateIndirect
CALL CC CHECKBOX_Default
CALL CC CHECKBOX_GetState
CALL CC CHECKBOX_GetText
CALL CC CHECKBOX_Image
CALL CC CHECKBOX_IsChecked
CALL CC CHECKBOX_SetBkColor
CALL CC CHECKBOX_SetBoxBkColor
CALL CC CHECKBOX_SetDefaultImage
CALL CC CHECKBOX_SetFocusColor
CALL CC CHECKBOX_SetFont
CALL CC CHECKBOX_SetImage
CALL CC CHECKBOX_SetNumStates
CALL CC CHECKBOX_SetSpacing
CALL CC CHECKBOX_SetState
CALL CC CHECKBOX_SetText
CALL CC CHECKBOX_SetTextAlign
CALL CC CHECKBOX_SetTextColor
CALL CC DIALOG
CALL CC DROPDOWN
CALL CC DROPDOWN_AddString
CALL CC DROPDOWN_Create
CALL CC DROPDOWN_CreateIndirect
CALL CC DROPDOWN_Default
CALL CC DROPDOWN_DeleteItem
CALL CC DROPDOWN_GetNumItems
CALL CC DROPDOWN_InsertString
CALL CC DROPDOWN_ItemSpacing
CALL CC DROPDOWN_SetAutoScroll
CALL CC DROPDOWN_SetBkColor
CALL CC DROPDOWN_SetColor
CALL CC DROPDOWN_SetFont
CALL CC DROPDOWN_SetScrollbarColor
CALL CC DROPDOWN_SetScrollbarWidth
CALL CC DROPDOWN_SetTextAlign
CALL CC DROPDOWN_SetTextColor
CALL CC DROPDOWN_SetTextHeight
CALL CC EDIT
CALL CC EDIT_Create
CALL CC EDIT_CreateIndirect
CALL CC EDIT_Default
CALL CC EDIT_GetCursorPixelPos
CALL CC EDIT_GetCursorPos
CALL CC EDIT_GetNumChars
CALL CC EDIT_SetCursorAtChar
CALL CC EDIT_SetFocussable
CALL CC EDIT_SetInsertMode
CALL CC EDIT_SetpfAddKeyEx
CALL CC EDIT_SetpfUpdateBuffer
CALL CC EDIT_SetSel
CALL CC EDIT_SetTextMode
CALL CC EDITBin
CALL CC EDITDec
CALL CC EDITFloat
CALL CC EDITHex
CALL CC FRAMEWIN
CALL CC FRAMEWIN__UpdateButtons
CALL CC FRAMEWIN_AddMenu
CALL CC FRAMEWIN_Button
CALL CC FRAMEWIN_ButtonClose
CALL CC FRAMEWIN_ButtonMax
CALL CC FRAMEWIN_ButtonMin
CALL CC FRAMEWIN_Create
CALL CC FRAMEWIN_CreateIndirect
CALL CC FRAMEWIN_Default
CALL CC FRAMEWIN_Get
CALL CC FRAMEWIN_IsMinMax
CALL CC FRAMEWIN_MinMaxRest
CALL CC FRAMEWIN_SetBorderSize
CALL CC FRAMEWIN_SetColors
CALL CC FRAMEWIN_SetFont
CALL CC FRAMEWIN_SetResizeable
CALL CC FRAMEWIN_SetTitleHeight
CALL CC FRAMEWIN_SetTitleVis
CALL CC GRAPH
CALL CC GRAPH_CreateIndirect
CALL CC GRAPH_DATA_XY
CALL CC GRAPH_DATA_YT
CALL CC GRAPH_SCALE
CALL CC GUI_ARRAY
CALL CC GUI_ARRAY_DeleteItem
CALL CC GUI_ARRAY_InsertItem
CALL CC GUI_ARRAY_ResizeItem
CALL CC GUI_DRAW
CALL CC GUI_DRAW_BITMAP
CALL CC GUI_DRAW_BMP
CALL CC GUI_DRAW_Self
CALL CC GUI_DRAW_STREAMED
CALL CC GUI_EditBin
CALL CC GUI_EditDec
CALL CC GUI_EditFloat
CALL CC GUI_EditHex
CALL CC GUI_EditString
CALL CC GUI_HOOK
CALL CC HEADER
CALL CC HEADER__SetDrawObj
CALL CC HEADER_Bitmap
CALL CC HEADER_BMP
CALL CC HEADER_Create
CALL CC HEADER_CreateIndirect
CALL CC HEADER_GetSel
CALL CC HEADER_SetDragLimit
CALL CC HEADER_StreamedBitmap
CALL CC LISTBOX
CALL CC LISTBOX_Create
CALL CC LISTBOX_CreateIndirect
CALL CC LISTBOX_Default
CALL CC LISTBOX_DeleteItem
CALL CC LISTBOX_Font
CALL CC LISTBOX_GetItemText
CALL CC LISTBOX_GetNumItems
CALL CC LISTBOX_GetTextAlign
CALL CC LISTBOX_InsertString
CALL CC LISTBOX_ItemDisabled
CALL CC LISTBOX_ItemSpacing
CALL CC LISTBOX_MultiSel
CALL CC LISTBOX_ScrollStep
CALL CC LISTBOX_SetAutoScroll
CALL CC LISTBOX_SetBkColor
CALL CC LISTBOX_SetOwner
CALL CC LISTBOX_SetOwnerDraw
CALL CC LISTBOX_SetScrollbarColor
CALL CC LISTBOX_SetScrollbarWidth
CALL CC LISTBOX_SetString
CALL CC LISTBOX_SetTextAlign
CALL CC LISTBOX_SetTextColor
CALL CC LISTVIEW
CALL CC LISTVIEW_Create
CALL CC LISTVIEW_CreateIndirect
CALL CC LISTVIEW_Default
CALL CC LISTVIEW_DeleteAllRows
CALL CC LISTVIEW_DeleteColumn
CALL CC LISTVIEW_DeleteRow
CALL CC LISTVIEW_DisableRow
CALL CC LISTVIEW_GetBkColor
CALL CC LISTVIEW_GetFont
CALL CC LISTVIEW_GetItemText
CALL CC LISTVIEW_GetHeader
CALL CC LISTVIEW_GetNumColumns
CALL CC LISTVIEW_GetNumRows
CALL CC LISTVIEW_GetSel
CALL CC LISTVIEW_GetTextColor
CALL CC LISTVIEW_InsertRow
CALL CC LISTVIEW_SetAutoScroll
CALL CC LISTVIEW_SetBkColor
CALL CC LISTVIEW_SetColumnWidth
CALL CC LISTVIEW_SetFont
CALL CC LISTVIEW_SetGridVis
CALL CC LISTVIEW_SetItemColor
CALL CC LISTVIEW_SetItemText
CALL CC LISTVIEW_SetLBorder
CALL CC LISTVIEW_SetRBorder
CALL CC LISTVIEW_SetRowHeight
CALL CC LISTVIEW_SetSel
CALL CC LISTVIEW_SetSort
CALL CC LISTVIEW_SetTextAlign
CALL CC LISTVIEW_SetTextColor
CALL CC LISTVIEW_UserData
CALL CC MENU
CALL CC MENU__FindItem
CALL CC MENU_Attach
CALL CC MENU_CreateIndirect
CALL CC MENU_Default
CALL CC MENU_DeleteItem
CALL CC MENU_DisableItem
CALL CC MENU_EnableItem
CALL CC MENU_GetItem
CALL CC MENU_GetItemText
CALL CC MENU_GetNumItems
CALL CC MENU_InsertItem
CALL CC MENU_Popup
CALL CC MENU_SetBkColor
CALL CC MENU_SetBorderSize
CALL CC MENU_SetFont
CALL CC MENU_SetItem
CALL CC MENU_SetTextColor
CALL CC MESSAGEBOX
CALL CC MULTIEDIT
CALL CC MULTIEDIT_Create
CALL CC MULTIEDIT_CreateIndirect
CALL CC MULTIPAGE
CALL CC MULTIPAGE_Create
CALL CC MULTIPAGE_CreateIndirect
CALL CC MULTIPAGE_Default
CALL CC PROGBAR
CALL CC PROGBAR_SetBarColor
CALL CC PROGBAR_SetFont
CALL CC PROGBAR_SetMinMax
CALL CC PROGBAR_SetText
CALL CC PROGBAR_SetTextAlign
CALL CC PROGBAR_SetTextColor
CALL CC PROGBAR_SetTextPos
CALL CC PROGBAR_Create
CALL CC PROGBAR_CreateIndirect
CALL CC RADIO
CALL CC RADIO_Create
CALL CC RADIO_CreateIndirect
CALL CC RADIO_Default
CALL CC RADIO_GetText
CALL CC RADIO_Image
CALL CC RADIO_SetBkColor
CALL CC RADIO_SetDefaultImage
CALL CC RADIO_SetFont
CALL CC RADIO_SetGroupId
CALL CC RADIO_SetFocusColor
CALL CC RADIO_SetText
CALL CC RADIO_SetTextColor
CALL CC SCROLLBAR
CALL CC SCROLLBAR_Create
CALL CC SCROLLBAR_CreateIndirect
CALL CC SCROLLBAR_Defaults
CALL CC SCROLLBAR_GetValue
CALL CC SCROLLBAR_SetColor
CALL CC SCROLLBAR_SetWidth
CALL CC SLIDER
CALL CC SLIDER_Create
CALL CC SLIDER_CreateIndirect
CALL CC SLIDER_Default
CALL CC SLIDER_SetFocusColor
CALL CC TEXT
CALL CC TEXT_Create
CALL CC TEXT_CreateIndirect
CALL CC TEXT_Default
CALL CC TEXT_SetBkColor
CALL CC TEXT_SetFont
CALL CC TEXT_SetText
CALL CC TEXT_SetTextAlign
CALL CC TEXT_SetTextColor
CALL CC TEXT_SetWrapMode
CALL CC WIDGET
CALL CC WIDGET_Effect_3D
CALL CC WIDGET_Effect_3D1L
CALL CC WIDGET_Effect_3D2L
CALL CC WIDGET_Effect_None
CALL CC WIDGET_Effect_Simple
CALL CC WIDGET_FillStringInRect
CALL CC WIDGET_SetEffect
CALL CC WIDGET_SetWidth
CALL CC WINDOW
CALL CC WINDOW_Default
