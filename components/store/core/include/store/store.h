#ifndef STORE_STORE_HEADER
#define STORE_STORE_HEADER

#include <store/product.h>
#include <store/transaction.h>

namespace store
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Store
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ���������� / �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Store  (const char* store_name);
    Store  (const Store& source);
    ~Store ();

    Store& operator = (const Store& source);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Description () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �� ������������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool CanBuyProducts () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� � ������� (products_ids - ����������� ��������� ������ ��������������� ���������,
///products ������ ����� ��������� �� ��� ����������� ��������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (const ProductList& products)> LoadProductsCallback;

    void LoadProducts (const char* product_ids, const LoadProductsCallback& callback) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� / �������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (const Transaction&)> PurchaseCallback;
    
    xtl::connection RegisterTransactionUpdateHandler (const PurchaseCallback&);
    Transaction     BuyProduct                       (const char* product_id, size_t count, const PurchaseCallback& callback) const;
    Transaction     BuyProduct                       (const char* product_id, size_t count) const;
    void            RestorePurchases                 () const;    

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Store&);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Store&, Store&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IStore
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~IStore () {}

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual const char* GetDescription () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �� ������������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual bool CanBuyProducts () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� � ������� (products_ids - ����������� ��������� ������ ��������������� ���������,
///products ������ ����� ��������� �� ��� ����������� ��������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (const ProductList& products)> LoadProductsCallback;

    virtual void LoadProducts (const char* product_ids, const LoadProductsCallback& callback) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� / �������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (const Transaction&)> PurchaseCallback;

    virtual xtl::connection RegisterTransactionUpdateHandler (const PurchaseCallback&) = 0;
    virtual void            RestorePurchases                 () = 0;
    virtual Transaction     BuyProduct                       (const char* product_id, size_t count) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class StoreManager
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<IStore* (const char* store_name)> CreateStoreHandler;

    static void RegisterStore       (const char* id, const char* store_name_mask, const CreateStoreHandler& handler);
    static void UnregisterStore     (const char* id);
    static void UnregisterAllStores ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static bool IsStoreRegistered (const char* store_name);
};

}

#endif
