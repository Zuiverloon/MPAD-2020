import wx  

#######################################################
#Wxpython Lab4
#Drawing Beizer Curves
#ECNU 10185102124 ZJY
#didn't upload the resource (icon,cursor,menu,bitmap,etc...)
#only code
#maybe some bugs unfixed
#######################################################


class MyFrame(wx.Frame):
  def __init__(self):
    wx.Frame.__init__(self, None, -1, "BezierAndTriangle", size=(800, 600))
    self.bst=0
    self.tst=0
    self.beizer=True
    self.tri=False
    self.Bind(wx.EVT_PAINT, self.OnPaint)
    #self.Bind(wx.EVT_SIZE, self.OnSize)
    self.Bind(wx.EVT_MOTION, self.OnMouseMove)
    self.Bind(wx.EVT_LEFT_DOWN, self.OnLeftDown)
    self.Bind(wx.EVT_LEFT_UP, self.OnLeftUp)
    self.ps = [[],[],[],[]]
    self.pps=[[],[],[]]
    self.saveps=[]

    self.menubar=wx.MenuBar()
    self.fileMenu=wx.Menu();
    self.menubar.Append(self.fileMenu,"File")
    self.fileMenu.Append(101,"New")
    self.Bind(wx.EVT_MENU, self.OnNew, id=101)
    self.fileMenu.Append(102,"Open")
    self.Bind(wx.EVT_MENU, self.OnOpen, id=102)
    self.fileMenu.Append(103,"Save")
    self.Bind(wx.EVT_MENU, self.OnSave, id=103)
    self.fileMenu.Append(104,"Save as")
    self.Bind(wx.EVT_MENU, self.OnSaveAs, id=104)
    self.fileMenu.Append(105,"Recent")
    self.Bind(wx.EVT_MENU, self.OnRecent, id=105)
    self.fileMenu.Append(106,"Exit")
    self.Bind(wx.EVT_MENU, self.OnQuit, id=106)

    self.drawMenu=wx.Menu();
    self.menubar.Append(self.drawMenu,"Draw")
    self.drawMenu.Append(201,"Beizer","",wx.ITEM_RADIO)
    self.drawMenu.Append(202,"Triangle","",wx.ITEM_RADIO)
    self.Bind(wx.EVT_MENU_RANGE, self.OnDraw, id=201,id2=202)

    self.aboutMenu=wx.Menu();
    self.menubar.Append(self.aboutMenu,"About")
    self.aboutMenu.Append(301,"Help")
    self.Bind(wx.EVT_MENU, self.OnHelp, id=301)


    self.SetMenuBar(self.menubar)
    self.Show()


  def OnDraw(self,evt):
    item=self.GetMenuBar().FindItemById(evt.GetId())
    idn=item.GetId()
    if idn==201:
      self.bst=0
      self.tst=0
      self.Refresh()
      self.beizer=True
      self.tri=False
    elif idn==202:
      self.tri=True
      self.beizer=False
      self.bst=0
      self.tst=0
      self.Refresh()

  
  def OnNew(self,event):
    self.ps = [[],[],[],[]]
    self.pps=[[],[],[]]
    self.bst=0
    self.tst=0
    self.Refresh()
    mb=wx.MessageBox("ReNew Successfully!","New",wx.OK|wx.ICON_INFORMATION)
    

  def OnOpen(self,event):
    wildcard="All files(*.*)|*.*"
    dialog = wx.FileDialog(None,"Choose a file","","",wildcard,wx.FD_OPEN)
    if dialog.ShowModal()==wx.ID_OK:
      mb=wx.MessageBox("Sorry!Nothing to open","Open",wx.OK|wx.ICON_INFORMATION)
    dialog.Destroy()
    self.Refresh()

  def OnSave(self,event):
    if self.beizer==True:
      self.saveps=self.ps
      mb=wx.MessageBox("Save Beizer Successfully!","Save",wx.OK|wx.ICON_INFORMATION)
    else:
      self.saveps=self.pps
      mb=wx.MessageBox("Save Triangle Successfully!","Save",wx.OK|wx.ICON_INFORMATION)

  def OnSaveAs(self,event):
    if self.beizer==True:
      self.saveps=self.ps
      mb=wx.MessageBox("Save Beizer Successfully!(The same as save)","SaveAs",wx.OK|wx.ICON_INFORMATION)
    else:
      self.saveps=self.pps
      mb=wx.MessageBox("Save Triangle Successfully!(The same as save)","SaveAs",wx.OK|wx.ICON_INFORMATION)

  def OnRecent(self,event):
    if len(self.saveps)==3:
      dc=wx.ClientDC(self)
      dc.SetPen(wx.Pen("black", 5))
      dc.SetLogicalFunction(wx.INVERT)
      dc.DrawLine(self.saveps[0][0],self.saveps[0][1],self.saveps[2][0],self.saveps[2][1])
      dc.DrawLine(self.saveps[0][0],self.saveps[0][1],self.saveps[1][0],self.saveps[1][1])
      dc.DrawLine(self.saveps[2][0],self.saveps[2][1],self.saveps[1][0],self.saveps[1][1])
      mb=wx.MessageBox("Recent Triangle!","Recent",wx.OK|wx.ICON_INFORMATION)
    elif len(self.saveps)==4:
      dc=wx.ClientDC(self)
      dc.SetPen(wx.Pen("black", 5))
      dc.SetLogicalFunction(wx.INVERT)
      dc.DrawSpline([ (int(x),int(y)) for x,y in self.saveps])
      mb=wx.MessageBox("Recent Beizer!","Recent",wx.OK|wx.ICON_INFORMATION)
    else:
      mb=wx.MessageBox("You saved nothing!","Recent",wx.OK|wx.ICON_INFORMATION)
      
      
  def OnHelp(self,e):
    mb=wx.MessageBox(u"2020MPADLab8\n作者学号：10185102124 姓名：章君尧","2020MPADLab8",wx.OK|wx.ICON_INFORMATION)
  

  def OnLeftDown(self, event):
    #print(1)
    p = event.GetPosition()

    #beizer
    if self.beizer==True:
      if self.bst==0:
        self.bst=1
        self.ps[0]=p
        self.Refresh()
      elif self.bst==2:
        self.bst=3
        self.ps[1]=p
        self.Refresh()
      elif self.bst==4:
        self.bst=5
        self.ps[2]=p
        self.Refresh()

    #triangle
    if self.tri==True:
      if self.tst==0:
        self.tst=1
        self.pps[0]=p
        self.Refresh()
      elif self.tst==2:
        self.tst=3
        self.pps[1]=p
        self.Refresh()
        

  def OnLeftUp(self,event):
    #print(3)
    p = event.GetPosition()
    #beizer
    if self.beizer==True:
      if self.bst==1:
        self.bst=2
      elif self.bst==3:
        self.bst=4
      elif self.bst==5:
        self.bst=0

    #triangle
    if self.tri==True:
      if self.tst==1:
        self.tst=2
      elif self.tst==3:
        self.tst=0

  def OnMouseMove(self, event):
    #print(2)
    p = event.GetPosition()

    #beizer
    if self.beizer==True:
      if self.bst==1:
        self.ps[3]=p;
        self.ps[2]=p;
        self.Refresh()
      elif self.bst==3:
        self.ps[1]=p
        self.Refresh()
      elif self.bst==5:
        self.ps[2]=p
        self.Refresh()


    #triangle
    if self.tri==True:
      if self.tst==1:
        self.pps[2]=p
        self.Refresh()
      elif self.tst==3:
        self.pps[1]=p
        self.Refresh()
        
      

  def OnPaint(self, event):
    dc = wx.PaintDC(self)
    dc.SetPen(wx.Pen("black", 5))
    dc.SetLogicalFunction(wx.INVERT)
    if self.ps and self.bst==1:
      dc.DrawLine(self.ps[0][0],self.ps[0][1],self.ps[3][0],self.ps[3][1])
    elif self.ps and self.bst==3:
      dc.DrawSpline([ (int(x),int(y)) for x,y in self.ps])
    elif self.ps and self.bst==5:
      dc.DrawSpline([ (int(x),int(y)) for x,y in self.ps])

    if self.pps and self.tst==1:
      dc.DrawLine(self.pps[0][0],self.pps[0][1],self.pps[2][0],self.pps[2][1])
    elif self.pps and self.tst==3:
      dc.DrawLine(self.pps[0][0],self.pps[0][1],self.pps[2][0],self.pps[2][1])
      dc.DrawLine(self.pps[0][0],self.pps[0][1],self.pps[1][0],self.pps[1][1])
      dc.DrawLine(self.pps[2][0],self.pps[2][1],self.pps[1][0],self.pps[1][1])


  def OnQuit(self,e):
    self.Close()

    
if __name__ == '__main__':
  app = wx.App()
  frame = MyFrame()
  frame.Show(True)
  app.MainLoop()



