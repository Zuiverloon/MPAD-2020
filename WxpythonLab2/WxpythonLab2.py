# -*- coding: utf8 -*- 

import wx

#######################################################
#Wxpython Lab2
#changing the icon / operations on the menu
#ECNU 10185102124 ZJY
#didn't upload the resource (icon,cursor,menu,bitmap,etc...)
#only code
#maybe some bugs unfixed
#######################################################


class MyFrame(wx.Frame):
  def __init__(self):
    wx.Frame.__init__(self,None,-1,U"2020MPADLab4:Wx资源使用",size=(1024,768))
    panel = wx.Panel(self, -1)  

    menubar=wx.MenuBar()
    fileMenu=wx.Menu();
    self.text = wx.StaticText(panel,-1,u"当前使用：图标1",pos=(100,100))
    self.text1 = wx.StaticText(panel,-1,u"",pos=(200,100))
    self.text2 = wx.StaticText(panel,-1,u"",pos=(300,100))
    self.text3 = wx.StaticText(panel,-1,u"",pos=(200,200))
    self.text4 = wx.StaticText(panel,-1,u"",pos=(300,200))
    menubar.Append(fileMenu,u"&File")
    fileMenu.Append(101,u"&Exit\tctrl+shift+q")
    self.Bind(wx.EVT_MENU, self.OnQuit, id=101)

    
    iconMenu=wx.Menu();
    menubar.Append(iconMenu,u"图标(&I)")
    icon1=wx.Menu()
    iconMenu.Append(201,u"图标&1\tCtrl+x",u"",wx.ITEM_RADIO)
    iconMenu.Append(202,u"图标&2\tCtrl+y",u"",wx.ITEM_RADIO)
    iconMenu.Append(203,u"图标&3\tCtrl+z",u"",wx.ITEM_RADIO)
    self.Bind(wx.EVT_MENU_RANGE,self.OnIcon,id=201,id2=203)

      
    textMenu=wx.Menu();
    menubar.Append(textMenu,u"显示(&D)")  
    textMenu.Append(301,u"显示&1\tCtrl+1",u"",wx.ITEM_CHECK)
    textMenu.Append(302,u"图标&2\tCtrl+2",u"",wx.ITEM_CHECK)
    textMenu.Append(303,u"图标&3\tCtrl+3",u"",wx.ITEM_CHECK)
    textMenu.Append(304,u"图标&4\tCtrl+4",u"",wx.ITEM_CHECK)
    self.Bind(wx.EVT_MENU_RANGE,self.OnPre,id=301,id2=304)

    aboutMenu=wx.Menu();
    menubar.Append(aboutMenu,"关于(&A)")  
    aboutMenu.Append(401,"程序信息(&C)\tF1")
    self.Bind(wx.EVT_MENU,self.OnInfo,id=401)
    self.SetMenuBar(menubar)
    self.Show()

  def OnIcon(self,evt):
    item=self.GetMenuBar().FindItemById(evt.GetId())
    idn=item.GetId()
    dlg=wx.MessageDialog(None,u"修改？",u"修改图标?",wx.YES_NO|wx.ICON_INFORMATION)
    if dlg.ShowModal() == wx.ID_YES:
      if idn==201:
        icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
        frame.SetIcon(icon)
        frame.GetMenuBar().EnableTop(2,True)
        self.text.SetLabel(u"当前使用：图标1")
      elif idn==202:
        icon=wx.Icon(name="icon2.ico",type=wx.BITMAP_TYPE_ICO)
        frame.SetIcon(icon)
        frame.GetMenuBar().EnableTop(2,True)
        self.text.SetLabel(u"当前使用：图标2")
      elif idn==203:
        icon=wx.Icon(name="icon3.ico",type=wx.BITMAP_TYPE_ICO)
        frame.SetIcon(icon)
        frame.GetMenuBar().EnableTop(2,False)
        self.text.SetLabel(u"当前使用：图标3")
    
  def OnPre(self,evt):
    item=self.GetMenuBar().FindItemById(evt.GetId())
    idn=item.GetId()
    boo=evt.IsChecked()

    if idn==301 and boo:
      self.text1.SetLabel(u"显示信息：1")
    elif idn==301 and boo==False:
      self.text1.SetLabel("  ")
    elif idn==302 and boo==True:
      self.text2.SetLabel(u"显示信息：2")
    elif idn==302 and boo==False:
      self.text2.SetLabel("  ")
    elif idn==303 and boo==True:
      self.text3.SetLabel(u"显示信息：3")
    elif idn==303 and boo==False:
      self.text3.SetLabel("  ")
    elif idn==304 and boo==True:
      self.text4.SetLabel(u"显示信息：4")
    elif idn==304 and boo==False:
      self.text4.SetLabel("  ")
    

  def OnInfo(self,e):
    mb=wx.MessageBox(u"2020MPADLab4:Wx资源使用\n作者学号：10185102124 姓名：章君尧","2020MPADLab4:Wx资源使用",wx.OK|wx.ICON_INFORMATION)


  def OnQuit(self,e):
    self.Close()
    

if __name__ == '__main__':
  app=wx.App()
  frame=MyFrame()
  frame.Show(True)
  icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
  frame.SetIcon(icon)
  app.MainLoop()

