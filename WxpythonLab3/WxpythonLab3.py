# -*- coding: utf8 -*- 
import header
import wx

#######################################################
#Wxpython Lab3
#Using resources(dialogs,icons,switching between English/CHinese)
#ECNU 10185102124 ZJY
#didn't upload the resource (icon,cursor,menu,bitmap,etc...)
#only code
#maybe some bugs unfixed
#######################################################









class ModalDialog(wx.Dialog):

  def __init__(self):
    wx.Dialog.__init__(self,None,-1,"Dialog",size=(300,200))
    b1=wx.CheckBox(self,-1,u"位图1",pos=(25,15))
    b2=wx.CheckBox(self,-1,u"位图2",pos=(25,45))
    b3=wx.CheckBox(self,-1,u"位图3",pos=(25,75))

    if MyFrame.bit1==False:
      b1.SetValue(False)
    elif MyFrame.bit1==True:
      b1.SetValue(True)
    if MyFrame.bit2==False:
      b2.SetValue(False)
    elif MyFrame.bit2==True:
      b2.SetValue(True)
    if MyFrame.bit3==False:
      b3.SetValue(False)
    elif MyFrame.bit3==True:
      b3.SetValue(True)
     
    self.Bind(wx.EVT_CHECKBOX,self.OnMDC)
    okb=wx.Button(self,wx.ID_OK,"OK",pos=(100,15))
    okb.SetDefault()
    cancelb=wx.Button(self,wx.ID_CANCEL,"CANCEL",pos=(100,45))

  def OnMDC(self,evt):
    cb=evt.GetEventObject()

    if cb.GetLabel()==u"位图1":
      if MyFrame.bit1==True:
        MyFrame.bit1=False
      elif MyFrame.bit1==False:
        MyFrame.bit1=True
        
    if cb.GetLabel()==u"位图2":
      if MyFrame.bit2==True:
        MyFrame.bit2=False
      elif MyFrame.bit2==False:
        MyFrame.bit2=True
    if cb.GetLabel()==u"位图3":
      if MyFrame.bit3==True:
        MyFrame.bit3=False
      elif MyFrame.bit3==False:
        MyFrame.bit3=True

class ModallessDialog(wx.Dialog):

  def __init__(self):
    wx.Dialog.__init__(self,None,-1,"Modelless Dialog",size=(300,200))
    c1=wx.RadioButton(self,-1,u"位图1",pos=(25,15))
    c2=wx.RadioButton(self,-1,u"位图2",pos=(25,45))
    c3=wx.RadioButton(self,-1,u"位图3",pos=(25,75))

    if MyFrame.bit4==1:
      c1.SetValue(True)
    if MyFrame.bit4==2:
      c2.SetValue(True)
    if MyFrame.bit4==3:
      c3.SetValue(True)




    c1.Bind(wx.EVT_RADIOBUTTON,self.OnOne)
    c2.Bind(wx.EVT_RADIOBUTTON,self.OnTwo)
    c3.Bind(wx.EVT_RADIOBUTTON,self.OnThree)
    okb=wx.Button(self,wx.ID_OK,"OK",pos=(100,15))
    okb.SetDefault()
    cancelb=wx.Button(self,wx.ID_CANCEL,"CANCEL",pos=(100,45))

  def OnOne(self,evt):
    MyFrame.bit4=1
  def OnTwo(self,evt):
    MyFrame.bit4=2
  def OnThree(self,evt):
    MyFrame.bit4=3
    

    


class MyFrame(wx.Frame):
  title=header.Ctitle
  info=header.Cinfo
  cursortext=header.CCText[0]
  lang="C"
  bit1=False
  bit2=False
  bit3=False
  bit4=0
  
  def __init__(self):
    wx.Frame.__init__(self,None,-1,self.title,size=(1024,768))
    self.panel = wx.Panel(self, -1)  
    ima1=wx.Image(name="bitmap1.bmp",type=wx.BITMAP_TYPE_BMP)
    ima2=wx.Image(name="bitmap2.bmp",type=wx.BITMAP_TYPE_BMP)
    ima3=wx.Image(name="bitmap3.bmp",type=wx.BITMAP_TYPE_BMP)
    self.bmp1=ima1.ConvertToBitmap()
    self.bmp2=ima2.ConvertToBitmap()
    self.bmp3=ima3.ConvertToBitmap()
    #self.bb1=wx.StaticBitmap(panel,-1,bmp1,pos=(200,200))
    self.menubar=wx.MenuBar()
    self.fileMenu=wx.Menu();

    self.text = wx.StaticText(self.panel,-1,self.cursortext,pos=(100,100))
    self.bb1=wx.StaticBitmap(self.panel,-1,self.bmp1,pos=(300,200))
    self.bb1.Hide()
    self.bb2=wx.StaticBitmap(self.panel,-1,self.bmp2,pos=(300,300))
    self.bb2.Hide()
    self.bb3=wx.StaticBitmap(self.panel,-1,self.bmp3,pos=(300,400))
    self.bb3.Hide()
    self.bc1=wx.StaticBitmap(self.panel,-1,self.bmp1,pos=(400,200))
    self.bc1.Hide()
    self.bc2=wx.StaticBitmap(self.panel,-1,self.bmp2,pos=(400,300))
    self.bc2.Hide()
    self.bc3=wx.StaticBitmap(self.panel,-1,self.bmp3,pos=(400,400))
    self.bc3.Hide()
    

    self.menubar.Append(self.fileMenu,header.Cmenu[0])
    self.fileMenu.Append(101,header.Cmenu[1])
    self.Bind(wx.EVT_MENU, self.OnQuit, id=101)

    DialogMenu=wx.Menu();
    self.menubar.Append(DialogMenu,header.Cmenu[2])
    DialogMenu.Append(201,header.Cmenu[3],u"")
    DialogMenu.Append(202,header.Cmenu[4],u"")
    DialogMenu.Append(203,header.Cmenu[5],u"")
    #self.Bind(wx.EVT_MENU_RANGE,self.OnCursor,id=201,id2=203)
    self.Bind(wx.EVT_MENU,self.OnMd,id=201)
    self.Bind(wx.EVT_MENU,self.OnMld,id=202)
    self.Bind(wx.EVT_MENU,self.OnFile,id=203)



    CursorMenu=wx.Menu();
    self.menubar.Append(CursorMenu,header.Cmenu[6])
    CursorMenu.Append(301,header.Cmenu[7],u"",wx.ITEM_RADIO)
    CursorMenu.Append(302,header.Cmenu[8],u"",wx.ITEM_RADIO)
    CursorMenu.Append(303,header.Cmenu[9],u"",wx.ITEM_RADIO)
    self.Bind(wx.EVT_MENU_RANGE,self.OnCursor,id=301,id2=303)

      


    LangMenu=wx.Menu()
    self.menubar.Append(LangMenu,header.Cmenu[10])
    LangMenu.Append(401,header.Cmenu[11],u"",wx.ITEM_RADIO)
    LangMenu.Append(402,header.Cmenu[12],u"",wx.ITEM_RADIO)
    self.Bind(wx.EVT_MENU,self.OnChinese,id=401)
    self.Bind(wx.EVT_MENU,self.OnEnglish,id=402)
    
    

    aboutMenu=wx.Menu();
    self.menubar.Append(aboutMenu,header.Cmenu[13])  
    aboutMenu.Append(501,header.Cmenu[14])
    self.Bind(wx.EVT_MENU,self.OnInfo,id=501)
    self.SetMenuBar(self.menubar)
    self.Show()


  def OnMd(self,evt):
    dialog=ModalDialog()
    result=dialog.ShowModal()
    if self.bit1==True:
      self.bb1.Show()
    elif self.bit1==False:
      self.bb1.Hide()
    if self.bit2==True:
      self.bb2.Show()
    elif self.bit2==False:
      self.bb2.Hide()
    if self.bit3==True:
      self.bb3.Show()
    elif self.bit3==False:
      self.bb3.Hide()
    dialog.Destroy()




  def OnMld(self,evt):
    dialog=ModallessDialog()
    result=dialog.ShowModal()
    if self.bit4==1:
      self.bc1.Show()
      self.bc2.Hide()
      self.bc3.Hide()
    elif self.bit4==2:
      self.bc1.Hide()
      self.bc2.Show()
      self.bc3.Hide()
    elif self.bit4==3:
      self.bc1.Hide()
      self.bc2.Hide()
      self.bc3.Show()
    



  def OnFile(self,evt):
    wildcard="All files(*.*)|*.*"
    dialog = wx.FileDialog(None,"Choose a file","","",wildcard,wx.FD_OPEN)
    if dialog.ShowModal()==wx.ID_OK:
      if self.lang=="C":
        mb=wx.MessageBox(header.Cfile+dialog.GetPath(),header.Cft,wx.OK|wx.ICON_INFORMATION)

      elif self.lang=="E":
        mb=wx.MessageBox(header.Efile+dialog.GetPath(),header.Eft,wx.OK|wx.ICON_INFORMATION)
    dialog.Destroy()
    self.Refresh()




  def OnCursor(self,evt):
    #print(self.text)
    item=self.GetMenuBar().FindItemById(evt.GetId())
    idn=item.GetId()
    #dlg=wx.MessageDialog(None,u"修改？",u"修改图标?",wx.YES_NO|wx.ICON_INFORMATION)
    #if dlg.ShowModal() == wx.ID_YES:
    if idn==301:
      frame.SetCursor(wx.Cursor(wx.CURSOR_ARROW))
      if self.lang=="C":
        self.cursortext=header.CCText[0]
        self.text.SetLabel(self.cursortext)
      elif self.lang=="E":
        self.cursortext=header.ECText[0]
        self.text.SetLabel(self.cursortext)
    elif idn==302:
      #print("haha")
      frame.SetCursor(wx.Cursor(wx.CURSOR_CROSS))
      if self.lang=="C":
        self.cursortext=header.CCText[1]
        self.text.SetLabel(self.cursortext)
      elif self.lang=="E":
        self.cursortext=header.ECText[1]
        self.text.SetLabel(self.cursortext)
    elif idn==303:
      cursor=wx.Cursor(cursorName="cursor1.cur",type=wx.BITMAP_TYPE_CUR)
      frame.SetCursor(cursor)
      if self.lang=="C":
        self.cursortext=header.CCText[2]
        self.text.SetLabel(self.cursortext)
      elif self.lang=="E":
        self.cursortext=header.ECText[2]
        self.text.SetLabel(self.cursortext)    

    

  def OnInfo(self,e):
    mb=wx.MessageBox(self.info,self.title,wx.OK|wx.ICON_INFORMATION)

  def OnChinese(self,e):
    self.lang="C"
    self.info=header.Cinfo
    self.title=header.Ctitle
    self.menubar.SetMenuLabel(0,header.Cmenu[0])
    self.menubar.SetMenuLabel(1,header.Cmenu[2])
    self.menubar.SetMenuLabel(2,header.Cmenu[6])
    self.menubar.SetMenuLabel(3,header.Cmenu[10])
    self.menubar.SetMenuLabel(4,header.Cmenu[13])
    self.menubar.SetLabel(101,header.Cmenu[1])
    self.menubar.SetLabel(201,header.Cmenu[3])
    self.menubar.SetLabel(202,header.Cmenu[4])
    self.menubar.SetLabel(203,header.Cmenu[5])
    self.menubar.SetLabel(301,header.Cmenu[7])
    self.menubar.SetLabel(302,header.Cmenu[8])
    self.menubar.SetLabel(303,header.Cmenu[9])
    self.menubar.SetLabel(501,header.Cmenu[14])
    frame.SetTitle(self.title)
    if self.cursortext == header.ECText[0]:
      self.cursortext=header.CCText[0]
      self.text.SetLabel(self.cursortext)
    elif self.cursortext == header.ECText[1]:
      self.cursortext=header.CCText[1]
      self.text.SetLabel(self.cursortext)
    elif self.cursortext == header.ECText[2]:
      self.cursortext=header.CCText[2]
      self.text.SetLabel(self.cursortext)  

  def OnEnglish(self,e):
    self.lang="E"
    self.info=header.Einfo
    self.title=header.Etitle
    self.menubar.SetMenuLabel(0,header.Emenu[0])
    self.menubar.SetMenuLabel(1,header.Emenu[2])
    self.menubar.SetMenuLabel(2,header.Emenu[6])
    self.menubar.SetMenuLabel(3,header.Emenu[10])
    self.menubar.SetMenuLabel(4,header.Emenu[13])
    self.menubar.SetLabel(101,header.Emenu[1])
    self.menubar.SetLabel(201,header.Emenu[3])
    self.menubar.SetLabel(202,header.Emenu[4])
    self.menubar.SetLabel(203,header.Emenu[5])
    self.menubar.SetLabel(301,header.Emenu[7])
    self.menubar.SetLabel(302,header.Emenu[8])
    self.menubar.SetLabel(303,header.Emenu[9])
    self.menubar.SetLabel(501,header.Emenu[14])
    frame.SetTitle(self.title)
    if self.cursortext == header.CCText[0]:
      self.cursortext=header.ECText[0]
      self.text.SetLabel(self.cursortext)
    elif self.cursortext == header.CCText[1]:
      self.cursortext=header.ECText[1]
      self.text.SetLabel(self.cursortext)
    elif self.cursortext == header.CCText[2]:
      self.cursortext=header.ECText[2]
      self.text.SetLabel(self.cursortext)  
    

  def OnQuit(self,e):
    self.Close()
    

if __name__ == '__main__':
  app=wx.App()
  frame=MyFrame()
  frame.Show(True)
  frame.SetCursor(wx.Cursor(wx.CURSOR_ARROW))
  app.MainLoop()

