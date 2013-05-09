#include "shared.h"

using namespace render::low_level;
using namespace render::low_level::dx11;

/*
    �������� ���������� ��������� ��������� ������
*/

struct OutputManager::Impl: public DeviceObject
{
/// �����������
  Impl (const DeviceManager& device_manager)
    : DeviceObject (device_manager)
  {
  }
};

/*
    ����������� / ����������
*/

OutputManager::OutputManager (const DeviceManager& device_manager)
  : impl (new Impl (device_manager))
{
}

OutputManager::~OutputManager ()
{
}

/*
    �������� ��������� ��������� ������
*/

IBlendState* OutputManager::CreateBlendState (const BlendDesc& desc)
{
  try
  {
    return new BlendState (impl->GetDeviceManager (), desc);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::OutputManager::CreateBlendState");
    throw;
  }
}

IDepthStencilState* OutputManager::CreateDepthStencilState (const DepthStencilDesc& desc)
{
  try
  {
    return new DepthStencilState (impl->GetDeviceManager (), desc);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::OutputManager::CreateDepthStencilState");
    throw;
  }
}

IRasterizerState* OutputManager::CreateRasterizerState (const RasterizerDesc& desc)
{
  try
  {
    return new RasterizerState (impl->GetDeviceManager (), desc);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::OutputManager::CreateRasterizerState");
    throw;
  }
}
