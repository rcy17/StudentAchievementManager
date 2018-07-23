#ifndef STATE_H
#define STATE_H
//------------------------------------------------------------------------
//
//  �ļ���:   State.h
//
//  ����:   һ����������״̬�ӿڵĳ������ļ�
//
//------------------------------------------------------------------------

class CUser;

class CState
{
public:

  virtual ~CState(){}

  //�������ʱִ�еĺ���
  virtual void Enter(CUser*)=0;

  //״̬��������ʱִ�еĺ���
  virtual void Execute(CUser*)=0;

  //״̬�˳�ʱִ�еĺ���
  virtual void Exit(CUser*)=0;
};

#endif