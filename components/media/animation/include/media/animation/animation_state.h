#ifndef MEDIALIB_ANIMATION_STATE_HEADER
#define MEDIALIB_ANIMATION_STATE_HEADER

namespace xtl
{

//forward declaration
class trackable;

}

namespace media
{

namespace animation
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class AnimationState
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    AnimationState  ();
    AnimationState  (const AnimationState&);
    ~AnimationState ();

    AnimationState& operator = (const AnimationState&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Id () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void  SetTime (float time);
    float Time    () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void  SetWeight (float weight);
    float Weight    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ���������� �� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    xtl::trackable& GetTrackable () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (AnimationState&);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (AnimationState&, AnimationState&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ���������� �� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
xtl::trackable& get_trackable (const AnimationState&);

}

}

#endif
