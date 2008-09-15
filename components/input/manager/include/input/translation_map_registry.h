#ifndef INPUT_SYSTEM_TRANSLATION_MAP_REGISTRY_HEADER
#define INPUT_SYSTEM_TRANSLATION_MAP_REGISTRY_HEADER

#include <common/serializer_manager.h>

namespace input
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class TranslationMapRegistry
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������ (������� ������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    TranslationMapRegistry  ();
    TranslationMapRegistry  (const char* file_name);
    TranslationMapRegistry  (const TranslationMapRegistry&);    
    ~TranslationMapRegistry ();

    TranslationMapRegistry& operator = (const TranslationMapRegistry&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / �������� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Register   (const char* profile, const char* translation_map);
    void Unregister (const char* profile);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Find        (const char* profile) const;
    const char* FindNearest (const char* profile) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Clear ();    

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Load (const char* file_name);
    void Save (const char* file_name) const;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (TranslationMapRegistry& registry);
  
  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (TranslationMapRegistry& registry1, TranslationMapRegistry& registry2);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef common::ResourceSerializerManager<void (const char* file_name, TranslationMapRegistry& map), 
                                          void (const char* file_name, const TranslationMapRegistry& map)> TranslationMapRegistryManager;

}

#endif
