#ifndef MEDIALIB_ANIMATION_TARGET_BLENDER_HEADER
#define MEDIALIB_ANIMATION_TARGET_BLENDER_HEADER

#include <media/animation/channel.h>

namespace common
{

//forward declaration
class PropertyMap;

}

namespace media
{

namespace animation
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������������� ����� ������ � ����� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class PropertyNameMap
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ��������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PropertyNameMap  ();
    PropertyNameMap  (const PropertyNameMap&);
    ~PropertyNameMap ();
    
    PropertyNameMap& operator = (const PropertyNameMap&);
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        Set (const char* channel_name, const char* property_name);
    const char* Get (const char* channel_name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    void Reset (const char* channel_name);
    void Clear ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (PropertyNameMap&);
    
  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (PropertyNameMap&, PropertyNameMap&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class TargetBlender
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TargetBlender  ();
    TargetBlender  (const TargetBlender&);
    ~TargetBlender ();  

    TargetBlender& operator = (const TargetBlender&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddChannel        (AnimationState& state, const Channel& channel);
    void AddChannel        (AnimationState& state, const Channel& channel, const PropertyNameMap& name_map);
    void RemoveChannel     (AnimationState& state);
    void RemoveAllChannels ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������� ������� ������������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const common::PropertyMap& Properties () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� ������������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Update ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (TargetBlender&);
    
  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (TargetBlender&, TargetBlender&);

}

}

#endif