#ifndef MEDIALIB_RFX_EFFECT_HEADER
#define MEDIALIB_RFX_EFFECT_HEADER

#include <common/property_map.h>

namespace media
{

namespace rfx
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class TechniquePass
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TechniquePass  ();
    TechniquePass  (const TechniquePass&);
    ~TechniquePass ();
    
    TechniquePass& operator = (const TechniquePass&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TechniquePass Clone () const;
 
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Id () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� - ��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    common::PropertyMap Properties () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (TechniquePass&);
    
  private:
    struct Impl;  
  
    TechniquePass (Impl*);

  private:
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (TechniquePass&, TechniquePass&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Technique
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Technique  ();
    Technique  (const Technique&);
    ~Technique ();
    
    Technique& operator = (const Technique&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Technique Clone () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Id () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������
///////////////////////////////////////////////////////////////////////////////////////////////////  
    const char* Name    () const;
    void        SetName (const char* name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t PassesCount () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
          TechniquePass& Pass (size_t index);
    const TechniquePass& Pass (size_t index) const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � �������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t AddPass         (const TechniquePass&);
    void   RemovePass      (size_t index);
    void   RemoveAllPasses ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� - ��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    common::PropertyMap Properties () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Technique&);
    
  private:
    struct Impl;
    
    Technique (Impl*);

  private:
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Technique&, Technique&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum EffectParameterType
{
  EffectParameterType_Int,      //����� �����
  EffectParameterType_Float,    //������������ �����
  EffectParameterType_Int2,     //������ �� 2-� ����� �����
  EffectParameterType_Float2,   //������ �� 2-� ������������ �����
  EffectParameterType_Int3,     //������ �� 3-� ����� �����
  EffectParameterType_Float3,   //������ �� 3-� ������������ �����
  EffectParameterType_Int4,     //������ �� 4-� ����� �����
  EffectParameterType_Float4,   //������ �� 4-� ������������ �����
  EffectParameterType_Float2x2, //������� 2x2 ������������ �����
  EffectParameterType_Float3x3, //������� 3x3 ������������ �����
  EffectParameterType_Float4x4, //������� 4x4 ������������ �����

  EffectParameterType_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class EffectParameter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    EffectParameter  ();
    EffectParameter  (const EffectParameter&);
    ~EffectParameter ();

    EffectParameter& operator = (const EffectParameter&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    EffectParameter Clone () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Id () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    const char* Name    () const;
    void        SetName (const char* name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////        
    EffectParameterType Type    () const;
    void                SetType (EffectParameterType type);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� ���������� ���� � ���������
///////////////////////////////////////////////////////////////////////////////////////////////////        
    size_t ElementsCount    () const;
    void   SetElementsCount (size_t count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (EffectParameter&);

  private:
    struct Impl;
    
    EffectParameter (Impl*);
    
  private:
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (EffectParameter&, EffectParameter&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Effect
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Effect  ();
    Effect  (const Effect&);
    ~Effect ();

    Effect& operator = (const Effect&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Id () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Effect Clone () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t TechniquesCount () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
          rfx::Technique& Technique (size_t index);
    const rfx::Technique& Technique (size_t index) const;
          rfx::Technique& Technique (const char* name);
    const rfx::Technique& Technique (const char* name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    int FindTechnique (const char* name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t AddTechnique        (const rfx::Technique&);
    void   RemoveTechnique     (size_t index);
    void   RemoveTechnique     (const char* name);
    void   RemoveAllTechniques ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t ParametersCount () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
          EffectParameter& Parameter (size_t index);
    const EffectParameter& Parameter (size_t index) const;
          EffectParameter& Parameter (const char* name);
    const EffectParameter& Parameter (const char* name) const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    int FindParameter (const char* name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t AddParameter        (const EffectParameter& param);
    void   RemoveParameter     (size_t index);
    void   RemoveParameter     (const char* name);
    void   RemoveAllParameters ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� - ��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    common::PropertyMap Properties () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Effect&);

  private:
    struct Impl;
    
    Effect (Impl*);
    
  private:
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Effect&, Effect&);

}

}

#endif
