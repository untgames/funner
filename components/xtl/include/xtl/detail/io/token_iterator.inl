/*
    ������������
*/

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>::token_iterator ()
  : first (), last ()
  {}
  
template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>::token_iterator (base_iterator in_first, base_iterator in_last)
  : first (in_first), last (in_last)
  {}

/*
    ������������
*/

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>& token_iterator<Token, BaseIter>::operator = (const token_iterator& i)
{
  token_iterator (i).swap (*this);

  return *this;
}

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>& token_iterator<Token, BaseIter>::assign (base_iterator in_first, base_iterator in_last)
{
  token_iterator (in_first, in_last).swap (*this)

  return *this;
}

/*
    ��������� ������
*/

template <class Token, class BaseIter>
inline typename token_iterator<Token, BaseIter>::reference token_iterator<Token, BaseIter>::token () const
{
  return *first;
}

template <class Token, class BaseIter>
inline typename token_iterator<Token, BaseIter>::reference token_iterator<Token, BaseIter>::operator *  () const
{
  return *first;
}

template <class Token, class BaseIter>
inline typename token_iterator<Token, BaseIter>::pointer token_iterator<Token, BaseIter>::operator -> () const
{
  return &*first;
}

/*
    ���������� ��������� ������� / �������� �� �������
*/

template <class T>
size_t distance (T* first, T* last)
{
  return last - first;
}

template <class Token, class BaseIter>
inline typename token_iterator<Token, BaseIter>::size_type token_iterator<Token, BaseIter>::available () const
{
  return empty () ? 0 : distance (first, last);
}

template <class Token, class BaseIter>
inline bool token_iterator<Token, BaseIter>::empty () const
{
  return !(first < last);
}

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>::operator safe_bool () const
{
  return first < last ? &token_iterator::dummy : 0;
}

/*
    ����������
*/

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>& token_iterator<Token, BaseIter>::operator += (size_type step)
{
  first += step;
  return *this;  
}

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>& token_iterator<Token, BaseIter>::operator -= (size_type step)
{
  first -= step;
  return *this;
}

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter> token_iterator<Token, BaseIter>::operator + (size_type step) const
{
  return token_iterator (*this) += step;
}

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter> token_iterator<Token, BaseIter>::operator - (size_type step) const
{
  return token_iterator (*this) -= step;
}

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>& token_iterator<Token, BaseIter>::operator ++ ()
{
  ++first;
  return *this;
}

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>& token_iterator<Token, BaseIter>::operator ++ (int)
{
  token_iterator tmp = *this;

  ++first;
  
  return tmp;
}

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>& token_iterator<Token, BaseIter>::operator -- ()
{
  --first;
  return *this;
}

template <class Token, class BaseIter>
inline token_iterator<Token, BaseIter>& token_iterator<Token, BaseIter>::operator -- (int)
{
  token_iterator tmp = *this;

  --first;
  
  return tmp;
}

/*
    �����
*/

template <class Token, class BaseIter>
inline void token_iterator<Token, BaseIter>::swap (token_iterator& i)
{
  base_iterator tmp1 = i.first;
  i.first            = first;
  first              = tmp1;
  
  base_iterator tmp2 = i.last;
  i.last             = last;
  last               = tmp2;
}

template <class Token, class BaseIter>
inline void swap (token_iterator<Token, BaseIter>& a, token_iterator<Token, BaseIter>& b)
{
  a.swap (b);
}

/*
    ���������
*/

template <class Token, class BaseIter>
inline bool token_iterator<Token, BaseIter>::operator == (const token_iterator& i) const
{
  return first == i.first && last == i.last;
}

template <class Token, class BaseIter>
inline bool token_iterator<Token, BaseIter>::operator != (const token_iterator& i) const
{
  return !(*this == i);
}

/*
    �������� ���������
*/

template <class Token>
inline token_iterator<Token> make_token_iterator (Token* first, Token* last)
{
  return token_iterator<Token> (first, last);
}

template <class BaseIter>
inline token_iterator<typename iterator_traits<BaseIter>::value_type, BaseIter> make_token_iterator (BaseIter first, BaseIter last)
{
  return token_iterator<typename iterator_traits<BaseIter>::value_type, BaseIter> (first, last);
}

/*
    ������ �������
*/

template <class Ret, class Token, class BaseIter>
inline Ret get (token_iterator<Token, BaseIter>& iter, const Ret& default_value)
{
  Ret value;

  return read (iter, value) ? value : default_value;
}

/*
    ������ ������������ ��������
*/

namespace detail
{

template <class Token, class BaseIter, class OutIter>
inline bool read_iter (token_iterator<Token, BaseIter>& iter, OutIter& out_iter)
{
  return read (iter, *out_iter);
}

template <class Token, class BaseIter, class T1>
inline bool read_iter (token_iterator<Token, BaseIter>& iter, T1* out_iter)
{
  return read (iter, *out_iter);
}

template <class Token, class BaseIter, class Container>
inline bool read_iter (token_iterator<Token, BaseIter>& iter, stl::back_insert_iterator<Container>& out_iter)
{
  typename Container::value_type object;

  if (!read (iter, object))
    return false;

  *out_iter = object;

  return true;
}

template <class Token, class BaseIter, class Container>
inline bool read_iter (token_iterator<Token, BaseIter>& iter, stl::front_insert_iterator<Container>& out_iter)
{
  typename Container::value_type object;

  if (!read (iter, object))
    return false;

  *out_iter = object;

  return true;
}

template <class Token, class BaseIter, class Container>
inline bool read_iter (token_iterator<Token, BaseIter>& iter, stl::insert_iterator<Container>& out_iter)
{
  typename Container::value_type object;

  if (!read (iter, object))
    return false;

  *out_iter = object;

  return true;
}

}

template <class Token, class BaseIter, class OutIter>
inline size_t read_range (token_iterator<Token, BaseIter>& iter, OutIter first, size_t count)
{
  size_t read_count = 0;
  
  for (;count-- && detail::read_iter (iter, first); ++first, ++read_count);

  return read_count;
}

template <class Token, class BaseIter, class OutIter>
inline size_t read_range (token_iterator<Token, BaseIter>& iter, OutIter first, size_t count, size_t step)
{
  if (!step)
    return read_range (iter, first, count);

  size_t                          read_count = 0;
  token_iterator<Token, BaseIter> next       = iter + step;

  for (;count-- && read_iter (iter, first); ++first, iter = next, next += step, ++read_count);

  return read_count;
}

/*
    ������ ������� ������� �����
*/

namespace detail
{

template <class Base, class Token, class BaseIter, class Value>
inline bool read_and_cast (token_iterator<Token, BaseIter>& iter, Value& value)
{
  Base base_value = 0;

  if (!read (iter, base_value))
    return false;

  value = static_cast<Value> (base_value);

  return true;
}

}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, long& value)
{
  if (!iter)
    return false;

  const char* src = *iter;  

  value = strtol (src, (char**)&src, 0);

  if (!*src)
  {
    ++iter;
    return true;
  }

  if (*src != '.')
    return false;

  while (*++src)
    if (!isdigit (*src))
      return false;

  ++iter;

  return true;  
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, unsigned long& value)
{
  return (iter, *(long*)&value);
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, char& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, unsigned char& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, short& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, unsigned short& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, int& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, unsigned int& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, double& value)
{
  if (!iter)
    return false;
    
  const char* src = *iter;

  value = strtod (src, (char**)&src);
  
  if (*src)
    return false;

  ++iter;

  return true;
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, float& value)
{
  return detail::read_and_cast<double> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const char*, BaseIter>& iter, long double& value)
{
  return detail::read_and_cast<double> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, long& value)
{
  if (!iter)
    return false;

  const wchar_t* src = *iter;  

  value = wsctol (src, (wchar_t**)&src, 0);

  if (!*src)
  {  
    ++iter;
    return true;
  }

  if (*src != L'.')
    return false;

  while (*++src)
    if (!iswdigit (*src))
      return false;

  ++iter;

  return true;  
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, unsigned long& value)
{
  return (iter, *(long*)&value);
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, char& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, unsigned char& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, short& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, unsigned short& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, int& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, unsigned int& value)
{
  return detail::read_and_cast<long> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, double& value)
{
  if (!iter)
    return false;
    
  const wchar_t* src = *iter;  

  value = wsctod (src, (wchar_t**)&src);
  
  if (*src)
    return false;

  ++iter;

  return true;
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, float& value)
{
  return detail::read_and_cast<double> (iter, value);
}

template <class BaseIter>
inline bool read (token_iterator<const wchar_t*, BaseIter>& iter, long double& value)
{
  return detail::read_and_cast<double> (iter, value);
}

/*
    ����������� ������    
*/

template <class Token, class BaseIter>
inline bool read (token_iterator<Token, BaseIter>& iter, Token& value)
{
  if (!iter)
    return false;
    
  value = *iter;
  
  ++iter;
  
  return true;
}

/*
    ������ STL �����
*/

template <class T, class BaseIter, class CharT, class Allocator>
inline bool read (token_iterator<const T*, BaseIter>& iter, stl::basic_string<T, CharT, Allocator>& s)
{
  if (!iter)
    return false;

  s = *iter;
  
  ++iter;

  return true;
}
