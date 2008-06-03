#include "shared.h"

using namespace common;

/*
    ������ �������������� ����������
*/

namespace
{

const char* extensions [] = {
  "GL_VERSION_1_1",
  "GL_VERSION_1_2",
  "GL_VERSION_1_3",
  "GL_VERSION_1_4",
  "GL_VERSION_1_5",
  "GL_VERSION_2_0",
  "GL_VERSION_2_1",
  "GL_3DFX_multisample",
  "GL_3DFX_tbuffer",
  "GL_3DFX_texture_compression_FXT1",
  "GL_APPLE_client_storage",
  "GL_APPLE_element_array",
  "GL_APPLE_fence",
  "GL_APPLE_float_pixels",
  "GL_APPLE_pixel_buffer",
  "GL_APPLE_specular_vector",
  "GL_APPLE_texture_range",
  "GL_APPLE_transform_hint",
  "GL_APPLE_vertex_array_object",
  "GL_APPLE_vertex_array_range",
  "GL_APPLE_ycbcr_422",
  "GL_ARB_color_buffer_float",
  "GL_ARB_depth_texture",
  "GL_ARB_draw_buffers",
  "GL_ARB_fragment_program",
  "GL_ARB_fragment_program_shadow",
  "GL_ARB_fragment_shader",
  "GL_ARB_half_float_pixel",
  "GL_ARB_imaging",
  "GL_ARB_matrix_palette",
  "GL_ARB_multisample",
  "GL_ARB_multitexture",
  "GL_ARB_occlusion_query",
  "GL_ARB_pixel_buffer_object",
  "GL_ARB_point_parameters",
  "GL_ARB_point_sprite",
  "GL_ARB_shader_objects",
  "GL_ARB_shading_language_100",
  "GL_ARB_shadow",
  "GL_ARB_shadow_ambient",
  "GL_ARB_texture_border_clamp",
  "GL_ARB_texture_compression",
  "GL_ARB_texture_cube_map",
  "GL_ARB_texture_env_add",
  "GL_ARB_texture_env_combine",
  "GL_ARB_texture_env_crossbar",
  "GL_ARB_texture_env_dot3",
  "GL_ARB_texture_float",
  "GL_ARB_texture_mirrored_repeat",
  "GL_ARB_texture_non_power_of_two",
  "GL_ARB_texture_rectangle",
  "GL_ARB_transpose_matrix",
  "GL_ARB_vertex_blend",
  "GL_ARB_vertex_buffer_object",
  "GL_ARB_vertex_program",
  "GL_ARB_vertex_shader",
  "GL_ARB_window_pos",
  "GL_ATIX_point_sprites",
  "GL_ATIX_texture_env_combine3",
  "GL_ATIX_texture_env_route",
  "GL_ATIX_vertex_shader_output_point_size",
  "GL_ATI_draw_buffers",
  "GL_ATI_element_array",
  "GL_ATI_envmap_bumpmap",
  "GL_ATI_fragment_shader",
  "GL_ATI_map_object_buffer",
  "GL_ATI_pn_triangles",
  "GL_ATI_separate_stencil",
  "GL_ATI_shader_texture_lod",
  "GL_ATI_text_fragment_shader",
  "GL_ATI_texture_compression_3dc",
  "GL_ATI_texture_env_combine3",
  "GL_ATI_texture_float",
  "GL_ATI_texture_mirror_once",
  "GL_ATI_vertex_array_object",
  "GL_ATI_vertex_attrib_array_object",
  "GL_ATI_vertex_streams",
  "GL_EXT_422_pixels",
  "GL_EXT_Cg_shader",
  "GL_EXT_abgr",
  "GL_EXT_bgra",
  "GL_EXT_bindable_uniform",
  "GL_EXT_blend_color",
  "GL_EXT_blend_equation_separate",
  "GL_EXT_blend_func_separate",
  "GL_EXT_blend_logic_op",
  "GL_EXT_blend_minmax",
  "GL_EXT_blend_subtract",
  "GL_EXT_clip_volume_hint",
  "GL_EXT_cmyka",
  "GL_EXT_color_subtable",
  "GL_EXT_compiled_vertex_array",
  "GL_EXT_convolution",
  "GL_EXT_coordinate_frame",
  "GL_EXT_copy_texture",
  "GL_EXT_cull_vertex",
  "GL_EXT_depth_bounds_test",
  "GL_EXT_draw_buffers2",
  "GL_EXT_draw_instanced",
  "GL_EXT_draw_range_elements",
  "GL_EXT_fog_coord",
  "GL_EXT_fragment_lighting",
  "GL_EXT_framebuffer_blit",
  "GL_EXT_framebuffer_multisample",
  "GL_EXT_framebuffer_object",
  "GL_EXT_framebuffer_sRGB",
  "GL_EXT_geometry_shader4",
  "GL_EXT_gpu_program_parameters",
  "GL_EXT_gpu_shader4",
  "GL_EXT_histogram",
  "GL_EXT_index_array_formats",
  "GL_EXT_index_func",
  "GL_EXT_index_material",
  "GL_EXT_index_texture",
  "GL_EXT_light_texture",
  "GL_EXT_misc_attribute",
  "GL_EXT_multi_draw_arrays",
  "GL_EXT_multisample",
  "GL_EXT_packed_depth_stencil",
  "GL_EXT_packed_float",
  "GL_EXT_packed_pixels",
  "GL_EXT_paletted_texture",
  "GL_EXT_pixel_buffer_object",
  "GL_EXT_pixel_transform",
  "GL_EXT_pixel_transform_color_table",
  "GL_EXT_point_parameters",
  "GL_EXT_polygon_offset",
  "GL_EXT_rescale_normal",
  "GL_EXT_scene_marker",
  "GL_EXT_secondary_color",
  "GL_EXT_separate_specular_color",
  "GL_EXT_shadow_funcs",
  "GL_EXT_shared_texture_palette",
  "GL_EXT_stencil_clear_tag",
  "GL_EXT_stencil_two_side",
  "GL_EXT_stencil_wrap",
  "GL_EXT_subtexture",
  "GL_EXT_texture",
  "GL_EXT_texture3D",
  "GL_EXT_texture_array",
  "GL_EXT_texture_buffer_object",
  "GL_EXT_texture_compression_dxt1",
  "GL_EXT_texture_compression_latc",
  "GL_EXT_texture_compression_rgtc",
  "GL_EXT_texture_compression_s3tc",
  "GL_EXT_texture_cube_map",
  "GL_EXT_texture_edge_clamp",
  "GL_EXT_texture_env",
  "GL_EXT_texture_env_add",
  "GL_EXT_texture_env_combine",
  "GL_EXT_texture_env_dot3",
  "GL_EXT_texture_filter_anisotropic",
  "GL_EXT_texture_integer",
  "GL_EXT_texture_lod_bias",
  "GL_EXT_texture_mirror_clamp",
  "GL_EXT_texture_object",
  "GL_EXT_texture_perturb_normal",
  "GL_EXT_texture_rectangle",
  "GL_EXT_texture_sRGB",
  "GL_EXT_texture_shared_exponent",
  "GL_EXT_timer_query",
  "GL_EXT_vertex_array",
  "GL_EXT_vertex_shader",
  "GL_EXT_vertex_weighting",
  "GL_GREMEDY_string_marker",
  "GL_HP_convolution_border_modes",
  "GL_HP_image_transform",
  "GL_HP_occlusion_test",
  "GL_HP_texture_lighting",
  "GL_IBM_cull_vertex",
  "GL_IBM_multimode_draw_arrays",
  "GL_IBM_rasterpos_clip",
  "GL_IBM_static_data",
  "GL_IBM_texture_mirrored_repeat",
  "GL_IBM_vertex_array_lists",
  "GL_INGR_color_clamp",
  "GL_INGR_interlace_read",
  "GL_INTEL_parallel_arrays",
  "GL_INTEL_texture_scissor",
  "GL_KTX_buffer_region",
  "GL_MESAX_texture_stack",
  "GL_MESA_pack_invert",
  "GL_MESA_resize_buffers",
  "GL_MESA_window_pos",
  "GL_MESA_ycbcr_texture",
  "GL_NV_blend_square",
  "GL_NV_copy_depth_to_color",
  "GL_NV_depth_buffer_float",
  "GL_NV_depth_clamp",
  "GL_NV_depth_range_unclamped",
  "GL_NV_evaluators",
  "GL_NV_fence",
  "GL_NV_float_buffer",
  "GL_NV_fog_distance",
  "GL_NV_fragment_program",
  "GL_NV_fragment_program2",
  "GL_NV_fragment_program4",
  "GL_NV_fragment_program_option",
  "GL_NV_framebuffer_multisample_coverage",
  "GL_NV_geometry_program4",
  "GL_NV_geometry_shader4",
  "GL_NV_gpu_program4",
  "GL_NV_half_float",
  "GL_NV_light_max_exponent",
  "GL_NV_multisample_filter_hint",
  "GL_NV_occlusion_query",
  "GL_NV_packed_depth_stencil",
  "GL_NV_parameter_buffer_object",
  "GL_NV_pixel_data_range",
  "GL_NV_point_sprite",
  "GL_NV_primitive_restart",
  "GL_NV_register_combiners",
  "GL_NV_register_combiners2",
  "GL_NV_texgen_emboss",
  "GL_NV_texgen_reflection",
  "GL_NV_texture_compression_vtc",
  "GL_NV_texture_env_combine4",
  "GL_NV_texture_expand_normal",
  "GL_NV_texture_rectangle",
  "GL_NV_texture_shader",
  "GL_NV_texture_shader2",
  "GL_NV_texture_shader3",
  "GL_NV_transform_feedback",
  "GL_NV_vertex_array_range",
  "GL_NV_vertex_array_range2",
  "GL_NV_vertex_program",
  "GL_NV_vertex_program1_1",
  "GL_NV_vertex_program2",
  "GL_NV_vertex_program2_option",
  "GL_NV_vertex_program3",
  "GL_NV_vertex_program4",
  "GL_OES_byte_coordinates",
  "GL_OES_compressed_paletted_texture",
  "GL_OES_read_format",
  "GL_OES_single_precision",
  "GL_OML_interlace",
  "GL_OML_resample",
  "GL_OML_subsample",
  "GL_PGI_misc_hints",
  "GL_PGI_vertex_hints",
  "GL_REND_screen_coordinates",
  "GL_S3_s3tc",
  "GL_SGIS_color_range",
  "GL_SGIS_detail_texture",
  "GL_SGIS_fog_function",
  "GL_SGIS_generate_mipmap",
  "GL_SGIS_multisample",
  "GL_SGIS_pixel_texture",
  "GL_SGIS_sharpen_texture",
  "GL_SGIS_texture4D",
  "GL_SGIS_texture_border_clamp",
  "GL_SGIS_texture_edge_clamp",
  "GL_SGIS_texture_filter4",
  "GL_SGIS_texture_lod",
  "GL_SGIS_texture_select",
  "GL_SGIX_async",
  "GL_SGIX_async_histogram",
  "GL_SGIX_async_pixel",
  "GL_SGIX_blend_alpha_minmax",
  "GL_SGIX_clipmap",
  "GL_SGIX_depth_texture",
  "GL_SGIX_flush_raster",
  "GL_SGIX_fog_offset",
  "GL_SGIX_fog_texture",
  "GL_SGIX_fragment_specular_lighting",
  "GL_SGIX_framezoom",
  "GL_SGIX_interlace",
  "GL_SGIX_ir_instrument1",
  "GL_SGIX_list_priority",
  "GL_SGIX_pixel_texture",
  "GL_SGIX_pixel_texture_bits",
  "GL_SGIX_reference_plane",
  "GL_SGIX_resample",
  "GL_SGIX_shadow",
  "GL_SGIX_shadow_ambient",
  "GL_SGIX_sprite",
  "GL_SGIX_tag_sample_buffer",
  "GL_SGIX_texture_add_env",
  "GL_SGIX_texture_coordinate_clamp",
  "GL_SGIX_texture_lod_bias",
  "GL_SGIX_texture_multi_buffer",
  "GL_SGIX_texture_range",
  "GL_SGIX_texture_scale_bias",
  "GL_SGIX_vertex_preclip",
  "GL_SGIX_vertex_preclip_hint",
  "GL_SGIX_ycrcb",
  "GL_SGI_color_matrix",
  "GL_SGI_color_table",
  "GL_SGI_texture_color_table",
  "GL_SUNX_constant_data",
  "GL_SUN_convolution_border_modes",
  "GL_SUN_global_alpha",
  "GL_SUN_mesh_array",
  "GL_SUN_read_video_pixels",
  "GL_SUN_slice_accum",
  "GL_SUN_triangle_list",
  "GL_SUN_vertex",
  "GL_WIN_phong_shading",
  "GL_WIN_specular_fog",
  "GL_WIN_swap_hint",
  
  "GLBUG_Texture3D_GetTexImage"
};

const size_t EXTENSIONS_COUNT = sizeof (extensions) / sizeof (*extensions);      

/*
    ��������� �������������� ������� ������������ ����� ��������� ������ ���������� � ��� ���������������
*/

class ExtensionMap
{
  public:
    ExtensionMap ()
    {
      map.resize (EXTENSIONS_COUNT);
      
      for (size_t i=0; i<EXTENSIONS_COUNT; i++)
        map [strihash (extensions [i])] = i;
    }
    
    size_t FindExtensionId (const char* name, size_t length) const
    {
      Map::const_iterator iter = map.find (strnihash (name, length));

      if (iter == map.end ())
        return EXTENSIONS_COUNT;

      return iter->second;
    }

  private:
    typedef stl::hash_map<size_t, size_t> Map;
    
  private:
    Map map;
};

}

namespace render
{

namespace low_level
{

namespace opengl
{

/*
    ��������� �������������� ���������� �� ���������� �����
*/

size_t get_extension_id (const char* full_name, size_t length)
{
  static const char* METHOD_NAME = "render::low_level::opengl::get_extension_id";

  if (!full_name)
    raise_null_argument (METHOD_NAME, "full_name");  

  typedef Singleton<ExtensionMap> ExtensionMapSingleton;

  return ExtensionMapSingleton::Instance ().FindExtensionId (full_name, length);
}

size_t get_extension_id (const char* full_name)
{
  return get_extension_id (full_name, full_name ? strlen (full_name) : 0);
}

/*
    ��������� ����� ���������� �� ��������������
*/

const char* get_extension_name (size_t id)
{
  if (id >= EXTENSIONS_COUNT)
    raise_out_of_range ("render::low_level::opengl::get_extension_name", "id", id, EXTENSIONS_COUNT);

  return extensions [id];
}

/*
    class Extension
*/

//������������
Extension::Extension (size_t in_id)
  : id (in_id)
{
  if (id >= EXTENSIONS_COUNT)
    raise_out_of_range ("render::low_level::opengl::Extension::Extension", "id", id, EXTENSIONS_COUNT);
}

Extension::Extension (const char* full_name)
  : id (get_extension_id (full_name))
{
  if (id >= EXTENSIONS_COUNT)
    raise_not_supported ("render::low_level::opengl::Extension::Extension", "Extension '%s' not supported", full_name);
}

//��� ����������
const char* Extension::Name () const
{
  return extensions [id];
}

/*
    class ExtensionSet
*/

struct ExtensionSet::Impl
{
  typedef stl::bitset<EXTENSIONS_COUNT> Bitset;
  
  Bitset flags;
};

//������������
ExtensionSet::ExtensionSet ()
  : impl (new Impl)
{
}

ExtensionSet::ExtensionSet (const ExtensionSet& set)
  : impl (new Impl (*set.impl))
{
}

//����������
ExtensionSet::~ExtensionSet ()
{
  delete impl;
}

//������������
ExtensionSet& ExtensionSet::operator = (const ExtensionSet& set)
{
  ExtensionSet (set).Swap (*this);
  
  return *this;
}

//���������� ���������� � ���������
size_t ExtensionSet::Size ()
{
  return EXTENSIONS_COUNT;
}

//��������� ������
void ExtensionSet::Set (const Extension& extension, bool state)
{
  impl->flags.set (extension.Id (), state);
}

bool ExtensionSet::Get (const Extension& extension) const
{
  return impl->flags.test (extension.Id ());
}

void ExtensionSet::Set (bool state)
{
  if (state) impl->flags.set ();
  else       impl->flags.reset ();
}

//��������� ������ �� ������ ���������� ����� ���������� � wildcard �����
void ExtensionSet::SetGroup (const char* extension_names, bool state)
{
  stl::string mask;

  for (const char* pos=extension_names; *pos;)
  {
    for (;*pos && *pos==' '; ++pos);

    const char* first    = pos;
    bool        wildcard = false;

    for (bool loop=true; loop; ++pos)
      switch (*pos)
      {
        case '\0':
        case ' ':
          loop = false;
          break;
        case '?':
        case '*':
          wildcard = true;
        default:
          break;
      }

    if (!wildcard)
    {
      size_t extension_id = get_extension_id (first, size_t (pos-first-1));

      if (extension_id >= EXTENSIONS_COUNT)
        continue;

      impl->flags [extension_id] = state;
    }
    else
    {
      mask.assign (first, size_t (pos - first - 1));

      if (!strcmp (mask.c_str (), "*")) //��������� ������������ ������ ������� / ��������� ���� ������
      {
        Set (state);
      }
      else
      {
        for (size_t id=0; id<EXTENSIONS_COUNT; id++)
          if (wcimatch (extensions [id], mask.c_str ()))
            impl->flags.set (id, state);
      }
    }    
  }
}

//���������� ��������
ExtensionSet& ExtensionSet::operator |= (const ExtensionSet& set)
{
  impl->flags |= set.impl->flags;

  return *this;
}

ExtensionSet& ExtensionSet::operator &= (const ExtensionSet& set)
{
  impl->flags &= set.impl->flags;
  
  return *this;
}

//�����
void ExtensionSet::Swap (ExtensionSet& set)
{
  Impl* tmp = set.impl;
  set.impl  = impl;
  impl      = tmp;
}

void swap (ExtensionSet& set1, ExtensionSet& set2)
{
  set1.Swap (set2);
}

}

}

}
