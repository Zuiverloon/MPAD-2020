
# -*- coding: utf8 -*- 
import wx


#######################################################
#Quiz May.08
#Changing background color / Popmenu
#ECNU 10185102124 ZJY
#didn't upload the resource (icon,cursor,menu,bitmap,etc...)
#only code
#maybe some bugs unfixed
#######################################################


    

    


class MyFrame(wx.Frame):
  
  
  def __init__(self):
    wx.Frame.__init__(self,None,-1,"PopMenu",size=(1024,768))
    self.panel = wx.Panel(self)

    self.popmenu=wx.Menu()
    self.File=wx.Menu()
    self.popmenu.Append(-1,"&File",self.File)
    self.IdCommand=self.File.Append(-1, u"命令(&R)\tCtrl+R", "This the text in the Statusbar")
    self.Bind(wx.EVT_MENU, self.OnCommand, self.IdCommand)
    self.Exit=self.File.Append(wx.ID_EXIT, u"E&xit\tAlt-X", u"Exit this simple sample")
    self.Bind(wx.EVT_MENU, self.OnClose, id=wx.ID_EXIT)

    #popmenu=wx.Menu()
    #File=wx.Menu()
    #popmenu.Append(-1,"&File",File)
    #IdCommand=File.Append(-1, u"命令(&R)\tCtrl+R", "This the text in the Statusbar")
    #self.Bind(wx.EVT_MENU, self.OnCommand, IdCommand)
    #Exit=File.Append(wx.ID_EXIT, u"E&xit\tAlt-X", u"Exit this simple sample")
    #self.Bind(wx.EVT_MENU, self.OnClose, id=wx.ID_EXIT)

    self.Color=wx.Menu()
    self.popmenu.Append(-1,"&Color",self.Color)
    self.Color.Append(201, u"White", u"", wx.ITEM_RADIO)
    self.Color.Append(202, u"Gray", u"", wx.ITEM_RADIO)
    self.Color.Append(203, u"Black", u"", wx.ITEM_RADIO)
    self.Bind(wx.EVT_MENU_RANGE, self.OnColor,id=201,id2=203)
    

    Control=wx.Menu()
    self.popmenu.Append(-1,"&Control",Control)
    Control.Append(301, u"Enable", u"Enable/Disable BG change", wx.ITEM_CHECK)
    self.Bind(wx.EVT_MENU, self.OnControl,id=301)
    self.popmenu.Check(301,True)
    self.changeable = True

    Help=wx.Menu()
    self.popmenu.Append(-1,"&Help",Help)
    About=Help.Append(-1, u"&About\tF1", u"Help tip")
    self.Bind(wx.EVT_MENU, self.OnHelp, About)



    
    #self.Color=wx.Menu()
    #self.popmenu.Append(-1,"&Color",self.Color)
    #Control=self.popmenu.Append(-1,"&Control")
    #Help=self.popmenu.Append(-1,"&Help")

    self.Bind(wx.EVT_CONTEXT_MENU,self.PopM)
    self.Bind(wx.EVT_PAINT, self.OnPaint)




  def OnPaint(self, evt):
    dc=wx.PaintDC(self)
    # draw something in client area
    evt.Skip()

  def OnCommand(self, evt):
    wx.MessageBox(u"Sorry,运行命令 not implemented yet！",
           "Message", 
		   wx.OK | wx.ICON_EXCLAMATION, self)


  def OnClose(self, evt):
    self.Close()

  def OnColor(self, evt):
    #item = self.GetMenuBar().FindItemById(evt.GetId())
    if evt.GetId()==201:
      text = u"White"
    elif evt.GetId()==202:
      text = u"Gray"
    elif evt.GetId()==203:
      text = u"Black"
    wx.MessageBox(u"You selected item '%s'" % text,
           u"Color Menu", wx.OK | wx.ICON_INFORMATION, self)
    if self.changeable:
      self.SetBackgroundColour(text)
      self.Refresh()
    else:
      dc=wx.ClientDC(self)
      dc.SetTextForeground(u'red')
      dc.DrawText(u"不能改变BG!",200,200)

  def OnControl(self, evt):
    self.changeable = evt.IsChecked()
#    self.GetMenuBar().Enable(self.IdCommand, self.changeable)
    self.popmenu.Enable(self.IdCommand.GetId(), self.changeable)

  def OnHelp(self, evt):
    wx.MessageBox(u"This is a wxPython program for Quiz\n 学号 10185102124 姓名：章君尧",
           u"About Menu", wx.OK | wx.ICON_INFORMATION, self)

  def PopM(self,event):
    pos = event.GetPosition()
    #print( pos)
    pos = self.panel.ScreenToClient(pos)
    #print( pos)
    self.panel.PopupMenu(self.popmenu,pos)





  




  
    

if __name__ == '__main__':
  app=wx.App()
  frame=MyFrame()
  frame.Show(True)
  app.MainLoop()
