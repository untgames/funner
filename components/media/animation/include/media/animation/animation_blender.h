#ifndef MEDIALIB_ANIMATION_BLENDER_HEADER
#define MEDIALIB_ANIMATION_BLENDER_HEADER

#include <media/animation/target_blender.h>

namespace media
{

namespace animation
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum AnimationBlenderEvent
{
  AnimationBlenderEvent_OnTargetAdded,   //��������� ����� ������������ ����
  AnimationBlenderEvent_OnTargetRemoved, //������� ������������ ����
  
  AnimationBlenderEvent_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class AnimationBlender
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    AnimationState AddAnimation (const media::Animation&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t TargetsCount () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const animation::TargetBlender& TargetBlender (size_t index) const;
          animation::TargetBlender& TargetBlender (size_t index); 

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Update ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ������� �������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<AnimationBlenderEvent event, const char* target_name, animation::TargetBlender&> EventHandler;

    xtl::connection RegisterEventHandler (AnimationBlenderEvent event, const EventHandler& handler);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (AnimationBlender&);
    
  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (AnimationBlender&, AnimationBlender&);

}

}

#endif