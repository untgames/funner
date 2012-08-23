extern "C"
{

#include <b64/cencode.h>
#include <b64/cdecode.h>

}

#include <xtl/common_exceptions.h>

#include <common/strlib.h>

using namespace common;

namespace common
{

/*
    ���������� / ������������ � Base64
*/

void encode_base64 (size_t src_buffer_size, const void* src_buffer, stl::string& result)
{
  if (!src_buffer && src_buffer_size)
    throw xtl::make_null_argument_exception ("common::encode_base64", "src_buffer");
    
  if (!src_buffer)
    src_buffer = "";

  base64_encodestate state;

  base64_init_encodestate (&state);  
  
  size_t saved_result_size = result.size ();
  
  result.fast_resize (saved_result_size + src_buffer_size * 2 + 5);
  
  int dst_length = base64_encode_block ((const char*)src_buffer, src_buffer_size, &result [saved_result_size], &state);
  
  if (dst_length < 0)
    throw xtl::format_operation_exception ("common::encode_base64", "::base64_encode_block failed");
    
  result.fast_resize (saved_result_size + (size_t)dst_length);
}

void decode_base64 (size_t src_buffer_size, const char* src_buffer, stl::string& result)
{
  if (!src_buffer && src_buffer_size)
    throw xtl::make_null_argument_exception ("common::encode_base64", "src_buffer");
    
  if (!src_buffer)
    src_buffer = "";

  base64_decodestate state;

  base64_init_decodestate (&state);  
  
  size_t saved_result_size = result.size ();
  
  result.fast_resize (saved_result_size + src_buffer_size * 2 + 5);
  
  int dst_length = base64_decode_block ((const char*)src_buffer, src_buffer_size, &result [saved_result_size], &state);
  
  if (dst_length < 0)
    throw xtl::format_operation_exception ("common::decode_base64", "::base64_decode_block failed");
    
  result.fast_resize (saved_result_size + (size_t)dst_length);
}

}