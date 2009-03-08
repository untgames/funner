namespace detail
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����� ��� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class shared_counter
{
  public:
            shared_counter  () : use_counter (1), weak_counter (1) { }
    virtual ~shared_counter () { }

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����� use_count ���������� ������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void dispose () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����� weak_count ���������� ������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void destroy () { delete this; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� �� ��������� ������ ���� ��� ��� ��������� � ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void* get_deleter (const std::type_info&) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������/���������� ����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void add_ref_copy ()
    {
      atomic_increment (use_counter);
    }

    void release ()
    {
      if (atomic_decrement (use_counter) == 1)
      {
        dispose      ();
        weak_release ();
      }
    }

    bool add_ref_lock() // true on success
    {
      return atomic_conditional_increment (use_counter) != 0;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������/���������� weak_count
///////////////////////////////////////////////////////////////////////////////////////////////////
    void weak_add_ref ()
    {
      atomic_increment (weak_counter);
    }

    void weak_release ()
    {
      if (atomic_decrement (weak_counter) == 1)
        destroy ();
    }

    long use_count () const
    {
      return (long)use_counter;
    }

  private:
    int use_counter;
    int weak_counter;
};

}
