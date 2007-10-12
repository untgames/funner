#ifndef COMMONLIB_PARSER_HEADER
#define COMMONLIB_PARSER_HEADER

#include <xtl/token_iterator.h>
#include <math/io.h>
#include <string.h>

namespace common
{

//implementation forwards
struct ParseTreeImpl;
class  ParseNode;

template <class NodeType> class ParseNodeIterator;
template <class NodeType> class ParseNamesakeIterator;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������� ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ParseLogMessageType
{
  PARSE_LOG_FATAL_ERROR,  //����������� ������
  PARSE_LOG_ERROR,        //������
  PARSE_LOG_WARNING      //��������������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ParseLog
{
  public: 
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ � ������������
///////////////////////////////////////////////////////////////////////////////////////////////////  
    ParseLog  ();
    ~ParseLog ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ������ � ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool HasErrors   () const;
    bool HasWarnings () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Error    (const char* file_name, size_t line, const char* format, ...);
    void Warning  (const char* file_name, size_t line, const char* format, ...);
    void Error    (ParseNode* node, const char* format, ...);
    void Warning  (ParseNode* node, const char* format, ...);
    void VError   (const char* file_name, size_t line, const char* format, va_list list);
    void VWarning (const char* file_name, size_t line, const char* format, va_list list);
    void VError   (ParseNode* node, const char* format, va_list list);
    void VWarning (ParseNode* node, const char* format, va_list list);

    void FatalError  (const char* format, ...);
    void VFatalError (const char* format, va_list list);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t              MessagesCount () const;
    const char*         Message       (size_t index) const; //������� ������ ���������� �� ��������� �������!!!!
    ParseLogMessageType MessageType   (size_t index) const;

  private:
    ParseLog (const ParseLog&);
    void operator = (const ParseLog&);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ParseNode
{
  public: 
///////////////////////////////////////////////////////////////////////////////////////////////////
///���
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Tag () const; //��� ����

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t       AttributesCount () const;
    const char*  Attribute       (size_t index) const;
    const char*  Attribute       (size_t index, const char* default_value) const;
    const char** Attributes      () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    ParseNode* First () const; //������ �������
    ParseNode* Next  () const; //��������� ���� �� ������ ������ ��������

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����� �� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    ParseNode* First (const char* tag) const; //������ ������� � ��������� ������
    ParseNode* Next  (const char* tag) const; //��������� ���� �� ������ ������ �������� � ��������� ������

    ParseNode* NextNamesake () const; //��������� "����" �� ������ ������ ��������

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � ������������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* SourceName () const; //��� ��������� ������,  � ������� ���������� ����
    size_t      LineNumber () const; //����� ������

  private:
    ParseNode  ();
    ParseNode  (const ParseNode&);
    ~ParseNode ();

    void operator = (const ParseNode&);

  private:  
    char data [1];
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ ����� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class NextFun>
class ParseIterator
{
  public: 
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ParseIterator ();
    ParseIterator (ParseNode*);
    
    template <class NextFun1>
    ParseIterator (const ParseIterator<NextFun1>&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    ParseIterator& operator = (ParseNode*);
    
    template <class NextFun1> 
    ParseIterator& operator = (const ParseIterator<NextFun1>&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �� ������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ParseIterator& operator ++ ();
    ParseIterator  operator ++ (int);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ���� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ParseNode* operator -> () const;
    ParseNode& operator *  () const;

    operator ParseNode* () const { return node; }

  private:
    ParseNode* node;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Parser
{
  private:
    struct NextNodeFun         { ParseNode* operator () (ParseNode* node) const; };
    struct NextNamesakeNodeFun { ParseNode* operator () (ParseNode* node) const; };

  public:
    typedef ParseNode                            Node;
    typedef ParseIterator<NextNodeFun>           Iterator;
    typedef ParseIterator<NextNamesakeNodeFun>   NamesakeIterator;
    typedef xtl::io::token_iterator<const char*> AttributeIterator;    
    typedef ParseLog                             Log;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Parser  (const char* file_name, const char* format="auto");
    Parser  (const char* name, const char* buf, size_t buf_size, const char* format="auto");
    Parser  (ParseLog& log, const char* file_name, const char* format="auto");
    Parser  (ParseLog& log, const char* name, const char* buf, size_t buf_size, const char* format="auto");
    ~Parser ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Node* Root () const;
    
  private:
    Parser (const Parser&); //no impl
    Parser& operator = (const Parser&); //no impl

  private:
    ParseTreeImpl* impl;  
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
Parser::AttributeIterator make_attribute_iterator (ParseNode*);
Parser::AttributeIterator make_attribute_iterator (ParseNode*, const char* tag);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> bool read (ParseNode*, const char* tag, T& object);
template <class T> void read (ParseNode*, const char* tag, T& object, const T& default_value);

template <class Traits, class Allocator> 
void read (ParseNode*, const char* tag, stl::basic_string<char, Traits, Allocator>& string, const char* default_value);

template <class T> T get (ParseNode*, const char* tag, const T& default_value=T ());

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������� � ����������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> bool read (ParseLog&, ParseNode*, const char* tag, T& object);
template <class T> void read (ParseLog&, ParseNode*, const char* tag, T& object, const T& default_value);

template <class Traits, class Allocator> 
void read (ParseLog&, ParseNode*, const char* tag, stl::basic_string<char, Traits, Allocator>& string, const char* default_value);

template <class T> T get (ParseLog&, ParseNode*, const char* tag, const T& default_value=T ());

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class OutIter>
size_t read_range (ParseNode*, const char* tag, OutIter first, size_t count=size_t(-1));

template <class OutIter>
size_t read_range (ParseNode*, const char* tag, OutIter first, size_t count, size_t start, size_t step=0);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ���������� � ����������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class OutIter>
size_t read_range (ParseLog&, ParseNode*, const char* tag, OutIter first, size_t count=size_t(-1));

template <class OutIter>
size_t read_range (ParseLog&, ParseNode*, const char* tag, OutIter first, size_t count, size_t start, size_t step=0);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ���� / �������� ���������� ����� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
bool test     (ParseNode*, const char* tag);
bool test_tag (ParseNode*, const char* tag);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> bool test (ParseNode*, const char* tag, const T& value);

bool test (ParseNode*, const char* tag, const char* value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� �� ���� ��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Fn> void for_each_child (ParseNode*, Fn fn);
template <class Fn> void for_each_child (ParseNode*, const char* tag, Fn fn);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������, ���� ���������� ��������� ���� � ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Fn>             void parse_if (ParseNode*, const char* tag, Fn then_fn);
template <class Fn1, class Fn2> void parse_if (ParseNode*, const char* tag, Fn1 then_fn, Fn2 else_fn);

#include <common/detail/parser.inl>

}

#endif
