#include "shared.h"

using namespace media::spine;

/*
   Constructors / destructor / assignment
*/

Attachment::Attachment (const Attachment& source)
  : impl (source.impl)
{
  if (impl)
    impl->AddRef ();
}

Attachment::Attachment (AttachmentImpl* in_impl)
  : impl (in_impl)
{
  if (!impl)
    throw xtl::make_null_argument_exception ("media::spine::Attachment::Attachment (IAttachment*)", "impl");
}

Attachment::~Attachment ()
{
  impl->Release ();
}

Attachment& Attachment::operator = (const Attachment& source)
{
  Attachment (source).Swap (*this);

  return *this;
}

/*
   Name
*/

const char* Attachment::Name () const
{
  return impl->Name ();
}

/*
   Get Type and type-specific data. Returned object is owned by callee.
*/

AttachmentType Attachment::Type () const
{
  return impl->Type ();
}

const void* Attachment::TypeSpecificData () const
{
  return impl->TypeSpecificData ();
}

/*
   Swap
*/

void Attachment::Swap (Attachment& attachment)
{
  stl::swap (impl, attachment.impl);
}

namespace media
{

namespace spine
{

//template specialization

template <>
const PointAttachmentData* Attachment::AttachmentData<PointAttachmentData> () const
{
  if (Type () == AttachmentType_Point)
    return static_cast<const PointAttachmentData*> (TypeSpecificData ());

  return 0;
}

/*
   Swap
*/

void swap (Attachment& attachment1, Attachment& attachment2)
{
  attachment1.Swap (attachment2);
}

}

}
