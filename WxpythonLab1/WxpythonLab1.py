# -*- coding: utf8 -*- 

import psutil
import wx
#######################################################
#Wxpython Lab1
#Process list in Win/Linux
#ECNU 10185102124 ZJY
#didn't upload the resource (icon,cursor,bitmap,etc...)
#only code
#######################################################


class MyFrame(wx.Frame):
  def __init__(self):
    wx.Frame.__init__(self,None,-1,U"2020MPADLab2: Windows/Linux进程列表 作者学号：10185102124 姓名：章君尧",size=(1024,768))
    panel = wx.Panel(self,-1)
    hor=10
    ver=10
    vergap=20
    horgap=200
    wx.StaticText(panel,-1,U"进程id   模块名",pos=(10,10))
    ver+=vergap
    ACCESS_DENIED=''
    for pid in sorted(psutil.pids()):
      try:
        p = psutil.Process(pid)
        pinfo = p.as_dict(ad_value=ACCESS_DENIED)
        hello = wx.StaticText(panel,-1,"",pos=(hor,ver))
        hello.SetLabel(u"%05x  %s"%(pid,pinfo['name']))
        ver+=vergap;
        if ver>700:
          ver=10
          hor+=horgap;
          wx.StaticText(panel,-1,U"进程id   模块名",pos=(hor,ver))
          ver+=vergap;
      except psutil.NoSuchProcess: pass


if __name__ == '__main__':
  app=wx.App()
  frame=MyFrame()
  frame.Show(True)
  icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
  frame.SetIcon(icon)
  app.MainLoop()
