#ifndef SCENE_GRAPH_NODE_ARRAY_HEADER
#define SCENE_GRAPH_NODE_ARRAY_HEADER

#include <cstddef>

namespace scene_graph
{

//forward declaration
class Node;
class NodeArrayImpl;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� ��������� � ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum NodeArrayLinkMode
{
  NodeArrayLinkMode_AddRef,  //�������� �������� ������ (������)
  NodeArrayLinkMode_WeakRef, //������-������, ��� �������� ���� �� ������������� ��������� �� ���������
  
  NodeArrayLinkMode_Default = NodeArrayLinkMode_AddRef,

  NodeArrayLinkMode_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ����� (�������� �������� - ������� ������)
///////////////////////////////////////////////////////////////////////////////////////////////////
class NodeArray
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    explicit NodeArray  (NodeArrayLinkMode link_mode = NodeArrayLinkMode_Default);
             NodeArray  (const NodeArray&);
             ~NodeArray ();

    NodeArray& operator = (const NodeArray&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    NodeArrayLinkMode LinkMode () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� � ��������� / �������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size    () const;
    bool   IsEmpty () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Node& Item (size_t index) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� / �������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Add    (Node&);
    void   Remove (Node&);
    void   Remove (size_t index);
    void   Clear  ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ����� ��� �������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Capacity () const;
    void   Reserve  (size_t count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (NodeArray&);

  private:
    NodeArrayImpl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (NodeArray&, NodeArray&);

}

#endif