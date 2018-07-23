#ifndef STATE_H
#define STATE_H
//------------------------------------------------------------------------
//
//  文件名:   State.h
//
//  简述:   一个用来定义状态接口的抽象类文件
//
//------------------------------------------------------------------------

class CUser;

class CState
{
public:

  virtual ~CState(){}

  //进入程序时执行的函数
  virtual void Enter(CUser*)=0;

  //状态正常更新时执行的函数
  virtual void Execute(CUser*)=0;

  //状态退出时执行的函数
  virtual void Exit(CUser*)=0;
};

#endif