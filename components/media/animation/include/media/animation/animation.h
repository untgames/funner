#ifndef MEDIALIB_ANIMATION_ANIMATION_HEADER
#define MEDIALIB_ANIMATION_ANIMATION_HEADER

#include <media/animation/channel.h>
#include <media/animation/event_track.h>

namespace media
{

namespace animation
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Animation
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Animation  ();
    Animation  (const Animation&);
    ~Animation ();
    
    Animation& operator = (const Animation&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    Animation Clone () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Id () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name   () const;
    void        Rename (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t      TargetsCount () const;
    const char* TargetName   (size_t target_index) const; 
    int         FindTarget   (const char* target_name) const; //nothrow

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t ChannelsCount (size_t target_index) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const animation::Channel& Channel (size_t target_index, size_t channel_index) const;
          animation::Channel& Channel (size_t target_index, size_t channel_index);
          
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������/�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddChannel        (size_t target_index, const animation::Channel& channel);
    void AddChannel        (const char* target_name, const animation::Channel& channel);
    void RemoveChannel     (size_t target_index, size_t channel_index);
    void RemoveAllChannels (size_t target_index);
    void RemoveAllChannels ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const EventTrack Events () const;
          EventTrack Events ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Animation&);
    
  private:
    struct Impl;
    Impl* impl;

  private:
    Animation (Impl* impl);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Animation&, Animation&);

}

}

#endif