#ifndef GLUE_STATE
#error GLUE_STATE_NOT_DEFINED
#endif

#define SET_1(v1)               value[0] = v1;
#define SET_2(v1, v2)           value[0] = v1; value[1] = v2;
#define SET_3(v1, v2, v3)       value[0] = v1; value[1] = v2; value[2] = v3;
#define SET_4(v1, v2, v3, v4)   value[0] = v1; value[1] = v2; value[2] = v3; value[3] = v4;
#define SET_N(n, inc, stmt) \
   { \
      int i; \
      for (i = 0; i < n; i++) \
      { \
         stmt \
         value += inc; \
      } \
   }

GLUE_STATE(GLuint, gl_num_tex_units, 1, 1,
           _sym_glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (GLint *)value); /* DEFAULT NOT EFFECT */,
           _sym_glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (GLint *)value);)

GLUE_STATE(GLuint, gl_num_vertex_attribs, 1, 1,
           _sym_glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, (GLint *)value); /* DEFAULT NOT EFFECT */,
           _sym_glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, (GLint *)value);)

GLUE_STATE(GLuint, gl_array_buffer_binding, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint *)value);)
GLUE_STATE(GLuint, gl_element_array_buffer_binding, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, (GLint *)value);)
GLUE_STATE(GLuint, gl_framebuffer_binding, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *)value);)
// ANGLE_framebuffer_blit BEGIN (check gl_framebuffer_binding_read_used)
GLUE_STATE(GLuint, gl_framebuffer_binding_read, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING_ANGLE, (GLint *)value);)
GLUE_STATE(GLuint, gl_framebuffer_binding_draw, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING_ANGLE, (GLint *)value);)
// ANGLE_framebuffer_blit END
GLUE_STATE(GLuint, gl_renderbuffer_binding, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint *)value);)

GLUE_STATE(GLboolean, gl_blend, 1, 1, SET_1(GL_FALSE), _sym_glGetBooleanv(GL_BLEND, (GLboolean *)value);)
GLUE_STATE(GLboolean, gl_cull_face, 1, 1, SET_1(GL_FALSE), _sym_glGetBooleanv(GL_CULL_FACE, (GLboolean *)value);)
GLUE_STATE(GLboolean, gl_depth_test, 1, 1, SET_1(GL_FALSE), _sym_glGetBooleanv(GL_DEPTH_TEST, (GLboolean *)value);)
GLUE_STATE(GLboolean, gl_dither, 1, 1, SET_1(GL_TRUE), _sym_glGetBooleanv(GL_DITHER, (GLboolean *)value);)

GLUE_STATE(GLboolean, gl_polygon_offset_fill, 1, 1, SET_1(GL_FALSE), _sym_glGetBooleanv(GL_POLYGON_OFFSET_FILL, (GLboolean *)value);)
GLUE_STATE(GLboolean, gl_sample_alpha_to_coverage, 1, 1, SET_1(GL_FALSE), _sym_glGetBooleanv(GL_SAMPLE_ALPHA_TO_COVERAGE, (GLboolean *)value);)
GLUE_STATE(GLboolean, gl_sample_coverage, 1, 1, SET_1(GL_FALSE), _sym_glGetBooleanv(GL_SAMPLE_COVERAGE, (GLboolean *)value);)
GLUE_STATE(GLboolean, gl_scissor_test, 1, 1, SET_1(GL_FALSE), _sym_glGetBooleanv(GL_SCISSOR_TEST, (GLboolean *)value);)
GLUE_STATE(GLboolean, gl_stencil_test, 1, 1, SET_1(GL_FALSE), _sym_glGetBooleanv(GL_STENCIL_TEST, (GLboolean *)value);)

GLUE_STATE(GLint, gl_viewport, 4, 4,
           _sym_glGetIntegerv(GL_VIEWPORT, (GLint *)value); /* DEFAULT NOT EFFECT */,
           _sym_glGetIntegerv(GL_VIEWPORT, (GLint *)value);)

GLUE_STATE(GLuint, gl_current_program, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)value);)
GLUE_STATE(GLclampf, gl_color_clear_value, 4, 4, SET_4(0.0f, 0.0f, 0.0f, 0.0f), _sym_glGetFloatv(GL_COLOR_CLEAR_VALUE, (GLfloat *)value);)

GLUE_STATE(GLboolean, gl_color_writemask, 4, 4, SET_4(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE), _sym_glGetBooleanv(GL_COLOR_WRITEMASK, (GLboolean *)value);)
GLUE_STATE(GLclampf, gl_depth_range, 2, 2, SET_2(0.0f, 1.0f), _sym_glGetFloatv(GL_DEPTH_RANGE, (GLfloat *)value);)
GLUE_STATE(GLclampf, gl_depth_clear_value, 1, 1, SET_1(1.0f), _sym_glGetFloatv(GL_DEPTH_CLEAR_VALUE, (GLfloat *)value);)
GLUE_STATE(GLenum, gl_depth_func, 1, 1, SET_1(GL_LESS), _sym_glGetIntegerv(GL_DEPTH_FUNC, (GLint *)value);)
GLUE_STATE(GLboolean, gl_depth_writemask, 1, 1, SET_1(GL_TRUE), _sym_glGetBooleanv(GL_DEPTH_WRITEMASK, (GLboolean *)value);)
GLUE_STATE(GLenum, gl_cull_face_mode, 1, 1, SET_1(GL_BACK), _sym_glGetIntegerv(GL_CULL_FACE_MODE, (GLint *)value);)

GLUE_STATE(GLuint, gl_tex_2d_state, INITIAL_CTX->gl_num_tex_units[0], MAX_TEXTURE_UNITS,
           SET_N(INITIAL_CTX->gl_num_tex_units[0], 1, SET_1(0)),
           _get_texture_states(GL_TEXTURE_BINDING_2D, (GLint *)value);)
GLUE_STATE(GLuint, gl_tex_cube_state, INITIAL_CTX->gl_num_tex_units[0], MAX_TEXTURE_UNITS,
           SET_N(INITIAL_CTX->gl_num_tex_units[0], 1, SET_1(0)),
           _get_texture_states(GL_TEXTURE_BINDING_CUBE_MAP, (GLint *)value);)

GLUE_STATE(GLenum, gl_active_texture, 1, 1, SET_1(GL_TEXTURE0), _sym_glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint *)value))
GLUE_STATE(GLenum, gl_generate_mipmap_hint, 1, 1, SET_1(GL_DONT_CARE), _sym_glGetIntegerv(GL_GENERATE_MIPMAP_HINT, (GLint *)value))

GLUE_STATE(GLclampf, gl_blend_color, 4, 4, SET_4(0.0f, 0.0f, 0.0f, 0.0f), _sym_glGetFloatv(GL_BLEND_COLOR, (GLfloat *)value);)
GLUE_STATE(GLenum, gl_blend_src_rgb, 1, 1, SET_1(GL_ONE), _sym_glGetIntegerv(GL_BLEND_SRC_RGB, (GLint *)value);)
GLUE_STATE(GLenum, gl_blend_src_alpha, 1, 1, SET_1(GL_ONE), _sym_glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint *)value);)
GLUE_STATE(GLenum, gl_blend_dst_rgb, 1, 1, SET_1(GL_ZERO), _sym_glGetIntegerv(GL_BLEND_DST_RGB, (GLint *)value);)
GLUE_STATE(GLenum, gl_blend_dst_alpha, 1, 1, SET_1(GL_ZERO), _sym_glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint *)value);)
GLUE_STATE(GLenum, gl_blend_equation_rgb, 1, 1, SET_1(GL_FUNC_ADD), _sym_glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint *)value);)
GLUE_STATE(GLenum, gl_blend_equation_alpha, 1, 1, SET_1(GL_FUNC_ADD), _sym_glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint *)value);)


GLUE_STATE(GLenum, gl_stencil_func, 1, 1, SET_1(GL_ALWAYS), _sym_glGetIntegerv(GL_STENCIL_FUNC, (GLint *)value);)
GLUE_STATE(GLint, gl_stencil_ref, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_STENCIL_REF, (GLint *)value);)
GLUE_STATE(GLuintmask, gl_stencil_value_mask, 1, 1,
           _sym_glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint *)value); /* DEFAULT NOT EFFECT */,
           _sym_glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint *)value);)
GLUE_STATE(GLenum, gl_stencil_fail, 1, 1, SET_1(GL_KEEP), _sym_glGetIntegerv(GL_STENCIL_FAIL, (GLint *)value);)
GLUE_STATE(GLenum, gl_stencil_pass_depth_fail, 1, 1, SET_1(GL_KEEP), _sym_glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, (GLint *)value);)
GLUE_STATE(GLenum, gl_stencil_pass_depth_pass, 1, 1, SET_1(GL_KEEP), _sym_glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, (GLint *)value);)
GLUE_STATE(GLuintmask, gl_stencil_writemask, 1, 1,
           _sym_glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint *)value); /* DEFAULT NOT EFFECT */,
           _sym_glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint *)value);)

GLUE_STATE(GLenum, gl_stencil_back_func, 1, 1, SET_1(GL_ALWAYS), _sym_glGetIntegerv(GL_STENCIL_BACK_FUNC, (GLint *)value);)
GLUE_STATE(GLint, gl_stencil_back_ref, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_STENCIL_BACK_REF, (GLint *)value);)
GLUE_STATE(GLuintmask, gl_stencil_back_value_mask, 1, 1,
           _sym_glGetIntegerv(GL_STENCIL_BACK_VALUE_MASK, (GLint *)value); /* DEFAULT NOT EFFECT */,
           _sym_glGetIntegerv(GL_STENCIL_BACK_VALUE_MASK, (GLint *)value);)
GLUE_STATE(GLenum, gl_stencil_back_fail, 1, 1, SET_1(GL_KEEP), _sym_glGetIntegerv(GL_STENCIL_BACK_FAIL, (GLint *)value);)
GLUE_STATE(GLenum, gl_stencil_back_pass_depth_fail, 1, 1, SET_1(GL_KEEP), _sym_glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_FAIL, (GLint *)value);)
GLUE_STATE(GLenum, gl_stencil_back_pass_depth_pass, 1, 1, SET_1(GL_KEEP), _sym_glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_PASS, (GLint *)value);)
GLUE_STATE(GLuintmask, gl_stencil_back_writemask, 1, 1,
           _sym_glGetIntegerv(GL_STENCIL_BACK_WRITEMASK, (GLint *)value); /* DEFAULT NOT EFFECT */,
           _sym_glGetIntegerv(GL_STENCIL_BACK_WRITEMASK, (GLint *)value);)

GLUE_STATE(GLint, gl_stencil_clear_value, 1, 1, SET_1(0), _sym_glGetIntegerv(GL_STENCIL_CLEAR_VALUE, (GLint *)value);)

// MISC FLAG 1
GLUE_STATE(GLenum, gl_front_face, 1, 1, SET_1(GL_CCW), _sym_glGetIntegerv(GL_FRONT_FACE, (GLint *)value);)
GLUE_STATE(GLfloat, gl_line_width, 1, 1, SET_1(1.0f), _sym_glGetFloatv(GL_LINE_WIDTH, (GLfloat *)value);)
GLUE_STATE(GLfloat, gl_polygon_offset_factor, 1, 1, SET_1(0.0f), _sym_glGetFloatv(GL_POLYGON_OFFSET_FACTOR, (GLfloat *)value);)
GLUE_STATE(GLfloat, gl_polygon_offset_units, 1, 1, SET_1(0.0f), _sym_glGetFloatv(GL_POLYGON_OFFSET_UNITS, (GLfloat *)value);)
GLUE_STATE(GLclampf, gl_sample_coverage_value, 1, 1, SET_1(1.0f), _sym_glGetFloatv(GL_SAMPLE_COVERAGE_VALUE, (GLfloat *)value);)
GLUE_STATE(GLboolean, gl_sample_coverage_invert, 1, 1, SET_1(GL_FALSE), _sym_glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT, (GLboolean *)value);)
GLUE_STATE(GLenum, gl_fragment_shader_derivative_hint, 1, 1, SET_1(GL_DONT_CARE), _sym_glGetIntegerv(GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES, (GLint *)value);)

// MISC FLAG 2
GLUE_STATE(GLint, gl_scissor_box, 4, 4,
           _sym_glGetIntegerv(GL_SCISSOR_BOX, (GLint *)value); /* DEFAULT NOT EFFECT */,
           _sym_glGetIntegerv(GL_SCISSOR_BOX, (GLint *)value);)

GLUE_STATE(GLint, gl_pack_alignment, 1, 1, SET_1(4), _sym_glGetIntegerv(GL_PACK_ALIGNMENT, (GLint *)value);)
GLUE_STATE(GLint, gl_unpack_alignment, 1, 1, SET_1(4), _sym_glGetIntegerv(GL_UNPACK_ALIGNMENT, (GLint *)value);)

GLUE_STATE(GLuint, gl_vertex_array_buf_id, INITIAL_CTX->gl_num_vertex_attribs[0], MAX_VERTEX_ATTRIBS,
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, SET_1(0)),
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, _sym_glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, (GLint *)value);))
GLUE_STATE(GLboolean, gl_vertex_array_enabled, INITIAL_CTX->gl_num_vertex_attribs[0], MAX_VERTEX_ATTRIBS,
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, SET_1(GL_FALSE)),
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, _sym_glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, (GLint *)value);))
GLUE_STATE(GLint, gl_vertex_array_size, INITIAL_CTX->gl_num_vertex_attribs[0], MAX_VERTEX_ATTRIBS,
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, SET_1(4)),
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, _sym_glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_SIZE, (GLint *)value);))
GLUE_STATE(GLenum, gl_vertex_array_type, INITIAL_CTX->gl_num_vertex_attribs[0], MAX_VERTEX_ATTRIBS,
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, SET_1(GL_FLOAT)),
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, _sym_glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_TYPE, (GLint *)value);))
GLUE_STATE(GLboolean, gl_vertex_array_normalized, INITIAL_CTX->gl_num_vertex_attribs[0], MAX_VERTEX_ATTRIBS,
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, SET_1(GL_FALSE)),
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, _sym_glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, (GLint *)value);))
GLUE_STATE(GLsizei, gl_vertex_array_stride, INITIAL_CTX->gl_num_vertex_attribs[0], MAX_VERTEX_ATTRIBS,
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, SET_1(GL_FALSE)),
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, _sym_glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_STRIDE, (GLint *)value);))
GLUE_STATE(GLvoidptr, gl_vertex_array_pointer, INITIAL_CTX->gl_num_vertex_attribs[0], MAX_VERTEX_ATTRIBS,
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, SET_1(NULL)),
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 1, _sym_glGetVertexAttribPointerv(i, GL_VERTEX_ATTRIB_ARRAY_POINTER, (GLvoidptr *)value);))

GLUE_STATE(GLfloat, gl_vertex_attrib_value, 4 * INITIAL_CTX->gl_num_vertex_attribs[0], MAX_VERTEX_ATTRIBS,
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 4, SET_4(0, 0, 0, 1)),
           SET_N(INITIAL_CTX->gl_num_vertex_attribs[0], 4, _sym_glGetVertexAttribfv(i, GL_CURRENT_VERTEX_ATTRIB, (GLfloat *)value);))

