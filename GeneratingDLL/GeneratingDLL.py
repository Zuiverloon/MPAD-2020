#_*_coding:utf-8_*_
# above line indicates encoding is UTF-8

#######################################################
#Generating DLL
#different functions included in the DLL
#ECNU 10185102124 ZJY
#didn't upload the resource (icon,cursor,menu,bitmap,etc...)
#only code
#maybe some bugs unfixed
#######################################################

import wx
import ctypes
import sys
import numpy
from sympy import *
from matplotlib.backends.backend_wxagg import FigureCanvasWxAgg as FigureCanvas
from matplotlib.figure import Figure
#sys.path.append('.')

#x**2-y**2
#DLLNAME=r"./MAPDQuiz3DLL.DLL" if sys.platform=="win32" else r"./MPADQuiz3SO.so"

#DLLNAME=r"./Quiz3.DLL" if sys.platform=="win32" else r"./MPADQuiz3SO.so"
DLLNAME=r"./labt.DLL" if sys.platform=="win32" else r"./MPADQuiz3SO.so"
class MyFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, wx.ID_ANY, 'Test', size=(1024,768))
        panel = wx.Panel(self, wx.ID_ANY) 

        In00=wx.StaticText(panel, wx.ID_ANY, u"")
        In01=wx.StaticText(panel, wx.ID_ANY, u"")

        In1=wx.StaticText(panel, wx.ID_ANY, u"输入",pos=(60,100))
        self.InText1 = wx.TextCtrl(panel, wx.ID_ANY, "1 3 2 4 5\nd",  size=(350, 100),pos=(100,100),style=wx.TE_MULTILINE)



        self.InText1.SetInsertionPoint(0)

        
        

        self.In02=wx.StaticText(panel, wx.ID_ANY, u"the result",pos=(400 ,500))

        Compute=wx.Button(panel, wx.ID_ANY, u"排序", pos=(600, 100))
        
        self.Bind(wx.EVT_BUTTON, self.EvtCompute, Compute)

        show=wx.Button(panel, wx.ID_ANY, u"显示作者", pos=(500, 100))
        self.Bind(wx.EVT_BUTTON, self.EvtShow, show)

        
        In03=wx.StaticText(panel, wx.ID_ANY, u"")
        Exit=wx.Button(panel, wx.ID_ANY, u"退出", pos=(900, 100))
        self.Bind(wx.EVT_BUTTON, self.EvtExit, Exit)

        solve=wx.Button(panel, wx.ID_ANY, u"因式分解", pos=(700, 100))
        self.Bind(wx.EVT_BUTTON,self.EvtSolve,solve)

        Ex=wx.Button(panel, wx.ID_ANY, u"展开", pos=(800, 100))
        self.Bind(wx.EVT_BUTTON,self.EvtEx,solve)

        #sizer = wx.FlexGridSizer(cols=2, hgap=5, vgap=10)
        #sizer.AddMany([In00,In01, In1, self.InText1,Out1,self.OutText1,In02, Compute,In03, Exit])
        #panel.SetSizer(sizer)
        #self.SetSize(650,300)
        #self.Centre()
        

        
        self.cdll=ctypes.CDLL(DLLNAME)
        
        

    def EvtCompute(self, event):
        a=[x for x in self.InText1.GetValue().split()]
        pre=[]
        b=a[-1]
        a=a[:-1:]
        for i in range(0,len(a)):
            a[i]=int(a[i])
            pre.append(a[i])
        #print(a)
        #print(b)
        ArrayType=ctypes.c_int*100
        cArray=ArrayType(*a)
        #print(cArray)
        self.cdll.iSort.restype=ctypes.c_void_p
        ArrayType=ctypes.ARRAY(ctypes.c_int,3)
        self.cdll.iSort.argstype=[ArrayType,ctypes.c_int,ctypes.c_int]
        zero=0
        czero=ctypes.c_int(zero)
        one=1
        cone=ctypes.c_int(one)
        if b=='a':
            result=self.cdll.iSort(cArray,ctypes.c_int(len(a)),czero)
            #print(cArray)
            for i in range(len(a)):
                a[i]=cArray[i]
            #self.OutText1.SetLabel(str(result))
        elif b=='d':
            result=self.cdll.iSort(cArray,ctypes.c_int(len(a)),czero)
            #print(cArray)
            for i in range(len(a)):
                a[i]=cArray[i]
            #self.OutText1.SetLabel(str(result))
        
        print(pre)
        print(a)
        hor=[]
        for i in range(len(pre)):
            hor.append(i)
        self.scorePanel = wx.Panel(self)
        t_score = numpy.arange(1, len(pre) + 1, 1)
        s_score = numpy.array(pre)
        ss_score=numpy.array(a)
        self.figure_score = Figure()
        self.figure_score.set_figheight(3.6)
        self.figure_score.set_figwidth(7.8)
        self.axes_score = self.figure_score.add_subplot(111)
        self.axes_score.plot(t_score, s_score, 'ro', t_score, s_score, 'k')
        self.axes_score.set_title(u'My Scores')
        self.axes_score.grid(True)
        self.axes_score.set_xlabel('T')
        self.axes_score.set_ylabel('score')
        FigureCanvas(self.scorePanel, -1, self.figure_score)
        self.In02.SetLabel(str(a)+"没办法输出图片")



        
        
    def EvtShow(self,event):
        mb=wx.MessageBox(u"2020MPADTest\n作者学号：10185102124 姓名：章君尧","2020MPADTest",wx.OK|wx.ICON_INFORMATION)
        
    def EvtSolve(self,event):#因fen
        formula=self.InText1.GetValue()
        x=Symbol('x')
        y=Symbol('y')
        f=sympify(formula)
        print(f)
        print(type(f))
        #f=latex(f)
        #print(f)
        #print(type(f))
        #if formula.startswith('$'):
         # self.axes.clear()
          #formula=formula[1:]
        #self.axes.patch.set_facecolor('gray')
        #self.axes.axis("off")
        #self.lineColorIdx=(self.lineColorIdx+1)%len(self.lineColor)
        #exec(formula)
        #self.canvas.draw()
        res=f.factor()
        self.In02.SetLabel(str(res))

    def EvtEx(self,event):
        formula=self.InText1.GetValue()
        x=Symbol('x')
        y=Symbol('y')
        f=sympify(formula)
        res=expand(f)
        self.In02.SetLabel(str(res))
        

    def EvtExit(self, event): self.Destroy()

if __name__ == '__main__':
#    import os
#    os.chdir(r"your working directory")
    app = wx.App()
    frame = MyFrame()
    frame.Show()
    app.MainLoop()

