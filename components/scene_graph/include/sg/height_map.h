#ifndef SCENE_GRAPH_HEIGHT_MAP_HEADER
#define SCENE_GRAPH_HEIGHT_MAP_HEADER

#include <stl/auto_ptr.h>
#include <sg/entity.h>

namespace scene_graph
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum HeightMapEvent
{
  HeightMapEvent_OnSizesUpdate,    //���������� ������� ����
  HeightMapEvent_OnVerticesUpdate, //���������� ������� ����� �����
  
  HeightMapEvent_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class HeightMap: public Entity
{
  public:
    typedef xtl::com_ptr<HeightMap>       Pointer;
    typedef xtl::com_ptr<const HeightMap> ConstPointer;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    struct VertexDesc
    {
      float       height;
      math::vec3f normal;
      math::vec4f color;
      
      VertexDesc () : height (0.f) {}
    };

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static Pointer Create ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void   SetRowsCount    (size_t rows_count);
    void   SetColumnsCount (size_t columns_count);
    void   SetCellsCount   (size_t rows_count, size_t columns_count);
    size_t RowsCount       () const;
    size_t ColumnsCount    () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const VertexDesc* Vertices () const;
          VertexDesc* Vertices ();
    const VertexDesc& Vertex   (size_t row, size_t column) const;
          VertexDesc& Vertex   (size_t row, size_t column);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetVerticesHeight (float height);
    void SetVerticesNormal (const math::vec3f& normal);
    void SetVerticesColor  (const math::vec4f& color);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateVerticesNotify ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (HeightMap& sender, HeightMapEvent event_id)> EventHandler;    

    xtl::connection RegisterEventHandler (HeightMapEvent event, const EventHandler& handler);
    
    using Entity::RegisterEventHandler;    

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    HeightMap  ();
    ~HeightMap ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AcceptCore (Visitor&);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

#endif
