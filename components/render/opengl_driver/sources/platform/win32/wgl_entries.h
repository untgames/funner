#ifndef RENDER_GL_DRIVER_WGL_ENTRIES_HEADER
#define RENDER_GL_DRIVER_WGL_ENTRIES_HEADER

#include <shared/profile/gl/wglext.h>

namespace render
{

namespace low_level
{

namespace opengl
{

//forward declaration
class ILibrary;

namespace windows
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� ���������� WGL
///////////////////////////////////////////////////////////////////////////////////////////////////
struct WglExtensionEntries
{

  PFNWGLCREATEBUFFERREGIONARBPROC CreateBufferRegionARB;
  PFNWGLDELETEBUFFERREGIONARBPROC DeleteBufferRegionARB;
  PFNWGLSAVEBUFFERREGIONARBPROC SaveBufferRegionARB;
  PFNWGLRESTOREBUFFERREGIONARBPROC RestoreBufferRegionARB;
  PFNWGLGETEXTENSIONSSTRINGARBPROC GetExtensionsStringARB;
  PFNWGLGETPIXELFORMATATTRIBIVARBPROC GetPixelFormatAttribivARB;
  PFNWGLGETPIXELFORMATATTRIBFVARBPROC GetPixelFormatAttribfvARB;
  PFNWGLCHOOSEPIXELFORMATARBPROC ChoosePixelFormatARB;
  PFNWGLMAKECONTEXTCURRENTARBPROC MakeContextCurrentARB;
  PFNWGLGETCURRENTREADDCARBPROC GetCurrentReadDCARB;
  PFNWGLCREATEPBUFFERARBPROC CreatePbufferARB;
  PFNWGLGETPBUFFERDCARBPROC GetPbufferDCARB;
  PFNWGLRELEASEPBUFFERDCARBPROC ReleasePbufferDCARB;
  PFNWGLDESTROYPBUFFERARBPROC DestroyPbufferARB;
  PFNWGLQUERYPBUFFERARBPROC QueryPbufferARB;
  PFNWGLBINDTEXIMAGEARBPROC BindTexImageARB;
  PFNWGLRELEASETEXIMAGEARBPROC ReleaseTexImageARB;
  PFNWGLSETPBUFFERATTRIBARBPROC SetPbufferAttribARB;
  PFNWGLCREATECONTEXTATTRIBSARBPROC CreateContextAttribsARB;
  PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC CreateDisplayColorTableEXT;
  PFNWGLLOADDISPLAYCOLORTABLEEXTPROC LoadDisplayColorTableEXT;
  PFNWGLBINDDISPLAYCOLORTABLEEXTPROC BindDisplayColorTableEXT;
  PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC DestroyDisplayColorTableEXT;
  PFNWGLGETEXTENSIONSSTRINGEXTPROC GetExtensionsStringEXT;
  PFNWGLMAKECONTEXTCURRENTEXTPROC MakeContextCurrentEXT;
  PFNWGLGETCURRENTREADDCEXTPROC GetCurrentReadDCEXT;
  PFNWGLCREATEPBUFFEREXTPROC CreatePbufferEXT;
  PFNWGLGETPBUFFERDCEXTPROC GetPbufferDCEXT;
  PFNWGLRELEASEPBUFFERDCEXTPROC ReleasePbufferDCEXT;
  PFNWGLDESTROYPBUFFEREXTPROC DestroyPbufferEXT;
  PFNWGLQUERYPBUFFEREXTPROC QueryPbufferEXT;
  PFNWGLGETPIXELFORMATATTRIBIVEXTPROC GetPixelFormatAttribivEXT;
  PFNWGLGETPIXELFORMATATTRIBFVEXTPROC GetPixelFormatAttribfvEXT;
  PFNWGLCHOOSEPIXELFORMATEXTPROC ChoosePixelFormatEXT;
  PFNWGLSWAPINTERVALEXTPROC SwapIntervalEXT;
  PFNWGLGETSWAPINTERVALEXTPROC GetSwapIntervalEXT;
  PFNWGLALLOCATEMEMORYNVPROC AllocateMemoryNV;
  PFNWGLFREEMEMORYNVPROC FreeMemoryNV;
  PFNWGLGETSYNCVALUESOMLPROC GetSyncValuesOML;
  PFNWGLGETMSCRATEOMLPROC GetMscRateOML;
  PFNWGLSWAPBUFFERSMSCOMLPROC SwapBuffersMscOML;
  PFNWGLSWAPLAYERBUFFERSMSCOMLPROC SwapLayerBuffersMscOML;
  PFNWGLWAITFORMSCOMLPROC WaitForMscOML;
  PFNWGLWAITFORSBCOMLPROC WaitForSbcOML;
  PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC GetDigitalVideoParametersI3D;
  PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC SetDigitalVideoParametersI3D;
  PFNWGLGETGAMMATABLEPARAMETERSI3DPROC GetGammaTableParametersI3D;
  PFNWGLSETGAMMATABLEPARAMETERSI3DPROC SetGammaTableParametersI3D;
  PFNWGLGETGAMMATABLEI3DPROC GetGammaTableI3D;
  PFNWGLSETGAMMATABLEI3DPROC SetGammaTableI3D;
  PFNWGLENABLEGENLOCKI3DPROC EnableGenlockI3D;
  PFNWGLDISABLEGENLOCKI3DPROC DisableGenlockI3D;
  PFNWGLISENABLEDGENLOCKI3DPROC IsEnabledGenlockI3D;
  PFNWGLGENLOCKSOURCEI3DPROC GenlockSourceI3D;
  PFNWGLGETGENLOCKSOURCEI3DPROC GetGenlockSourceI3D;
  PFNWGLGENLOCKSOURCEEDGEI3DPROC GenlockSourceEdgeI3D;
  PFNWGLGETGENLOCKSOURCEEDGEI3DPROC GetGenlockSourceEdgeI3D;
  PFNWGLGENLOCKSAMPLERATEI3DPROC GenlockSampleRateI3D;
  PFNWGLGETGENLOCKSAMPLERATEI3DPROC GetGenlockSampleRateI3D;
  PFNWGLGENLOCKSOURCEDELAYI3DPROC GenlockSourceDelayI3D;
  PFNWGLGETGENLOCKSOURCEDELAYI3DPROC GetGenlockSourceDelayI3D;
  PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC QueryGenlockMaxSourceDelayI3D;
  PFNWGLCREATEIMAGEBUFFERI3DPROC CreateImageBufferI3D;
  PFNWGLDESTROYIMAGEBUFFERI3DPROC DestroyImageBufferI3D;
  PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC AssociateImageBufferEventsI3D;
  PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC ReleaseImageBufferEventsI3D;
  PFNWGLENABLEFRAMELOCKI3DPROC EnableFrameLockI3D;
  PFNWGLDISABLEFRAMELOCKI3DPROC DisableFrameLockI3D;
  PFNWGLISENABLEDFRAMELOCKI3DPROC IsEnabledFrameLockI3D;
  PFNWGLQUERYFRAMELOCKMASTERI3DPROC QueryFrameLockMasterI3D;
  PFNWGLGETFRAMEUSAGEI3DPROC GetFrameUsageI3D;
  PFNWGLBEGINFRAMETRACKINGI3DPROC BeginFrameTrackingI3D;
  PFNWGLENDFRAMETRACKINGI3DPROC EndFrameTrackingI3D;
  PFNWGLQUERYFRAMETRACKINGI3DPROC QueryFrameTrackingI3D;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� ����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
  void Init (ILibrary&);
};

}

}

}

}

#endif
