/* This is a generated file. DO NOT EDIT! */

static const FoldFunc fold_func[] = {
  fold_kfold_numarith,
  fold_kfold_fpmath,
  fold_kfold_numpow,
  fold_kfold_numcomp,
  fold_kfold_intarith,
  fold_kfold_intovarith,
  fold_kfold_bnot,
  fold_kfold_bswap,
  fold_kfold_intcomp,
  fold_kfold_intcomp0,
  fold_kfold_int64arith,
  fold_kfold_int64arith2,
  fold_kfold_int64shift,
  fold_kfold_bnot64,
  fold_kfold_bswap64,
  fold_kfold_int64comp,
  fold_kfold_int64comp0,
  fold_kfold_snew_kptr,
  fold_kfold_snew_empty,
  fold_kfold_strref,
  fold_kfold_strref_snew,
  fold_kfold_strcmp,
  fold_kfold_add_kgc,
  fold_kfold_add_kptr,
  fold_kfold_tobit,
  fold_kfold_conv_kint_num,
  fold_kfold_conv_kintu32_num,
  fold_kfold_conv_kint_i64,
  fold_kfold_conv_kint64_num_i64,
  fold_kfold_conv_kint64_num_u64,
  fold_kfold_conv_kint64_int_i64,
  fold_kfold_conv_knum_int_num,
  fold_kfold_conv_knum_u32_num,
  fold_kfold_conv_knum_i64_num,
  fold_kfold_conv_knum_u64_num,
  fold_kfold_tostr_knum,
  fold_kfold_tostr_kint,
  fold_kfold_strto,
  lj_opt_cse,
  fold_kfold_kref,
  fold_shortcut_round,
  fold_shortcut_left,
  fold_shortcut_dropleft,
  fold_shortcut_leftleft,
  fold_simplify_numadd_negx,
  fold_simplify_numadd_xneg,
  fold_simplify_numsub_k,
  fold_simplify_numsub_negk,
  fold_simplify_numsub_xneg,
  fold_simplify_nummuldiv_k,
  fold_simplify_nummuldiv_negk,
  fold_simplify_nummuldiv_negneg,
  fold_simplify_numpow_xk,
  fold_simplify_numpow_kx,
  fold_shortcut_conv_num_int,
  fold_simplify_conv_int_num,
  fold_simplify_conv_u32_num,
  fold_simplify_conv_i64_num,
  fold_simplify_conv_int_i64,
  fold_simplify_conv_flt_num,
  fold_simplify_tobit_conv,
  fold_simplify_floor_conv,
  fold_simplify_conv_sext,
  fold_simplify_conv_narrow,
  fold_cse_conv,
  fold_narrow_convert,
  fold_simplify_intadd_k,
  fold_simplify_intmul_k,
  fold_simplify_intsub_k,
  fold_simplify_intsub_kleft,
  fold_simplify_intadd_k64,
  fold_simplify_intsub_k64,
  fold_simplify_intmul_k32,
  fold_simplify_intmul_k64,
  fold_simplify_intsub,
  fold_simplify_intsubadd_leftcancel,
  fold_simplify_intsubsub_leftcancel,
  fold_simplify_intsubsub_rightcancel,
  fold_simplify_intsubadd_rightcancel,
  fold_simplify_intsubaddadd_cancel,
  fold_simplify_band_k,
  fold_simplify_bor_k,
  fold_simplify_bxor_k,
  fold_simplify_shift_ik,
  fold_simplify_shift_andk,
  fold_simplify_shift1_ki,
  fold_simplify_shift2_ki,
  fold_reassoc_intarith_k,
  fold_reassoc_intarith_k64,
  fold_reassoc_dup,
  fold_reassoc_bxor,
  fold_reassoc_shift,
  fold_reassoc_minmax_k,
  fold_reassoc_minmax_left,
  fold_reassoc_minmax_right,
  fold_abc_fwd,
  fold_abc_k,
  fold_abc_invar,
  fold_comm_swap,
  fold_comm_equal,
  fold_comm_comp,
  fold_comm_dup,
  fold_comm_bxor,
  fold_merge_eqne_snew_kgc,
  lj_opt_fwd_aload,
  fold_kfold_hload_kkptr,
  lj_opt_fwd_hload,
  lj_opt_fwd_uload,
  lj_opt_fwd_tab_len,
  fold_cse_uref,
  fold_fwd_href_tnew,
  fold_fwd_href_tdup,
  fold_fload_tab_tnew_asize,
  fold_fload_tab_tnew_hmask,
  fold_fload_tab_tdup_asize,
  fold_fload_tab_tdup_hmask,
  fold_fload_tab_ah,
  fold_fload_str_len_kgc,
  fold_fload_str_len_snew,
  fold_fload_cdata_typeid_kgc,
  fold_fload_cdata_int64_kgc,
  fold_fload_cdata_typeid_cnew,
  fold_fload_cdata_ptr_int64_cnew,
  lj_opt_cse,
  lj_opt_fwd_fload,
  fold_fwd_sload,
  fold_xload_kptr,
  lj_opt_fwd_xload,
  fold_barrier_tab,
  fold_barrier_tnew_tdup,
  lj_opt_dse_ahstore,
  lj_opt_dse_ustore,
  lj_opt_dse_fstore,
  lj_opt_dse_xstore,
  lj_ir_emit
};

static const uint32_t fold_hash[722] = {
0x7483fc06,
0x86b5ffff,
0x564a6bff,
0xffffffff,
0x454e53ff,
0xffffffff,
0x5443fc1e,
0x02566414,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x0c4a6814,
0x4a69ffff,
0x044e5014,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x424dfc14,
0x5a4083ff,
0xffffffff,
0x55446bff,
0xffffffff,
0x564853ff,
0xffffffff,
0x5d62c3ff,
0xffffffff,
0xffffffff,
0xffffffff,
0x57408014,
0xffffffff,
0x0c446814,
0x6563ffff,
0x04485014,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x5347fc14,
0xffffffff,
0xffffffff,
0xffffffff,
0x584c981a,
0x3250b019,
0x554253ff,
0x8617ffff,
0x0b54681a,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x2d4dfc2c,
0xffffffff,
0x27125415,
0x04425014,
0xffffffff,
0xffffffff,
0xffffffff,
0x5241fc14,
0x23aa6400,
0x80a3ffff,
0xffffffff,
0x00626419,
0x3d654c00,
0xffffffff,
0x6311ffff,
0x100bfc1a,
0x0a4e681a,
0x6e7133ff,
0x18a86419,
0xffffffff,
0x80a1fc00,
0xffffffff,
0x043c5014,
0x4951fc1a,
0xffffffff,
0x6d7657ff,
0x3aa74e75,
0xffffffff,
0x869dffff,
0xffffffff,
0x3ca94c19,
0x005c6419,
0xffffffff,
0xffffffff,
0x640bffff,
0x7483fc03,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x869bfc00,
0x6251ffff,
0xffffffff,
0xffffffff,
0x03106419,
0x3153fc19,
0x7b83fc0b,
0xffffffff,
0x8697ffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x6405ffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x030a6419,
0xffffffff,
0xffffffff,
0xffffffff,
0x8491ffff,
0xffffffff,
0xffffffff,
0x00506419,
0xffffffff,
0xffffffff,
0xffffffff,
0x0a3c681a,
0x0f0a6814,
0xffffffff,
0x080e5014,
0xffffffff,
0xffffffff,
0xffffffff,
0x513ffc1a,
0xffffffff,
0x03046419,
0xffffffff,
0xffffffff,
0x583e7c1a,
0x828bffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x5c62c414,
0xffffffff,
0xffffffff,
0x0f046814,
0xffffffff,
0x08085014,
0xffffffff,
0xffffffff,
0x653fffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x0e3a6800,
0x593e7fff,
0x7f85ffff,
0x056a5014,
0xffffffff,
0xffffffff,
0x174c581a,
0xffffffff,
0x4269fc14,
0xffffffff,
0xffffffff,
0xffffffff,
0x08025014,
0xffffffff,
0x7b83fc00,
0x4f4e9826,
0xffffffff,
0x1ea66a75,
0x26130418,
0xffffffff,
0xffffffff,
0x7882540c,
0x71833006,
0x06385000,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x7a833c0c,
0x3ea7feb3,
0x687dfc00,
0x5b468c14,
0xffffffff,
0xffffffff,
0x67112815,
0x2864c800,
0x164c541a,
0x147b2bff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x11945c14,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x574c9814,
0xffffffff,
0xffffffff,
0xffffffff,
0x1ea66a95,
0x8673ffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x3457fc14,
0xffffffff,
0xffffffff,
0x454e6bff,
0xffffffff,
0xffffffff,
0xffffffff,
0x5447fc1e,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x090bfc14,
0x5d60c7ff,
0xffffffff,
0x5c62c419,
0xffffffff,
0xffffffff,
0xffffffff,
0x4851fc14,
0x3d654c02,
0x86b3ffff,
0x56486bff,
0x2a5ab019,
0x81a13000,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x0c486814,
0x6267ffff,
0x044c5014,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x534bfc14,
0xffffffff,
0x19a651d3,
0x55426bff,
0x7483fc05,
0x6cb1fc08,
0x564653ff,
0x174c5c1a,
0x5960c3ff,
0xffffffff,
0x76832800,
0x583c781a,
0xffffffff,
0x0c426814,
0x6561ffff,
0x7b83fc0d,
0x04465014,
0x5c60c014,
0x6f713419,
0xffffffff,
0x5345fc14,
0x016467ff,
0x40a7ffff,
0x73833406,
0x2f4eb019,
0xffffffff,
0xffffffff,
0x6115ffff,
0x0b52681a,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x27105415,
0x04405014,
0xffffffff,
0xffffffff,
0xffffffff,
0x513ffc14,
0xffffffff,
0xffffffff,
0xffffffff,
0x00606419,
0x573e7c14,
0x41a69e6e,
0x640fffff,
0x0a4c681a,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x474ffc1a,
0x3fa69e76,
0xffffffff,
0x6d7457ff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x005a6419,
0xffffffff,
0x5b448814,
0x6409ffff,
0xffffffff,
0xffffffff,
0x174c5814,
0xffffffff,
0x2713fc18,
0xffffffff,
0x4a4fffff,
0xffffffff,
0x2b3a7400,
0x030e6419,
0x3151fc19,
0x5850a01a,
0x41a69a6e,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x7983380b,
0xffffffff,
0x6403ffff,
0x271263ff,
0x0a40681a,
0x0f0e6814,
0x3fa69a76,
0x27125014,
0x295ab419,
0x81a13400,
0xffffffff,
0xffffffff,
0x03086419,
0xffffffff,
0xffffffff,
0xffffffff,
0x838fffff,
0xffffffff,
0xffffffff,
0x164c5414,
0x004e6419,
0x697e5c00,
0xffffffff,
0xffffffff,
0x0f086814,
0xffffffff,
0x080c5014,
0xffffffff,
0xffffffff,
0x5c60c019,
0x2864c802,
0x503dfc1a,
0x03026419,
0x25ac5400,
0xffffffff,
0xffffffff,
0x7b89ffff,
0xffffffff,
0xffffffff,
0x2b58b3ff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x0f026814,
0x36a74dd3,
0x08065014,
0xffffffff,
0x41a69eae,
0x653dffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x0d386800,
0xffffffff,
0x7c83ffff,
0x1da669d6,
0x05685014,
0x2712681a,
0xffffffff,
0xffffffff,
0x4267fc14,
0xffffffff,
0xffffffff,
0xffffffff,
0x08005014,
0xffffffff,
0x6b81fc00,
0xffffffff,
0xffffffff,
0xffffffff,
0x26110418,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x04625014,
0x4d4ffc27,
0x2c4cb3ff,
0x3fa6a276,
0xffffffff,
0x41a69aae,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x593c7bff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x174c5c14,
0x6015fc14,
0xffffffff,
0x7782540b,
0x70833005,
0x573c7814,
0xffffffff,
0xffffffff,
0x3352b02c,
0xffffffff,
0xffffffff,
0x6f713413,
0x137a5414,
0xffffffff,
0xffffffff,
0x544bfc1e,
0x79833c0b,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x7471ffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x2b387000,
0x5445fc1e,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x41a89819,
0x626bffff,
0x04505014,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x444ffc14,
0x86b1ffff,
0xffffffff,
0x56466bff,
0x5b4a9414,
0x564a53ff,
0xffffffff,
0x1295fc14,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x0c466814,
0x1fa6666e,
0x044a5014,
0xffffffff,
0xffffffff,
0xffffffff,
0x86a40000,
0x5349fc14,
0xffffffff,
0xffffffff,
0x3d654c01,
0x5750a014,
0x3252b019,
0x554453ff,
0x37a74e6e,
0x0b56681a,
0x24aa5000,
0x75825400,
0xffffffff,
0xffffffff,
0x304ffc2c,
0xffffffff,
0x04445014,
0xffffffff,
0x3aa74e76,
0xffffffff,
0xffffffff,
0x5343fc14,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x7483fc04,
0xffffffff,
0x6313ffff,
0x0a50681a,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x043e5014,
0x7b83fc0c,
0xffffffff,
0x20a6668e,
0xffffffff,
0x503dfc14,
0xffffffff,
0xffffffff,
0xffffffff,
0x005e6419,
0x72833405,
0xffffffff,
0x640dffff,
0xffffffff,
0xffffffff,
0x5e61fc31,
0x38a74e8e,
0xffffffff,
0xffffffff,
0xffffffff,
0x464dfc1a,
0x3ba74dcd,
0x03126419,
0xffffffff,
0xffffffff,
0xffffffff,
0x355667ff,
0x8699ffff,
0x1ba652b3,
0x00586419,
0xffffffff,
0x5840801a,
0x6407ffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x2711fc18,
0x5e63fc30,
0x7e845fff,
0x624dffff,
0xffffffff,
0x030c6419,
0x2e4ffc19,
0x3fa69e75,
0xffffffff,
0x8593ffff,
0x21a666ae,
0x41a89c19,
0x00526419,
0x15af6c00,
0xffffffff,
0x6401ffff,
0x271063ff,
0x0a3e681a,
0x0f0c6814,
0x27105014,
0xffffffff,
0xffffffff,
0x39a74eae,
0x5241fc1a,
0xffffffff,
0x03066419,
0xffffffff,
0xffffffff,
0x5b428414,
0x828dffff,
0xffffffff,
0xffffffff,
0x004c6419,
0xffffffff,
0xffffffff,
0x1ba652d3,
0xffffffff,
0x0f066814,
0xffffffff,
0x080a5014,
0x3fa69a75,
0xffffffff,
0x6641ffff,
0xffffffff,
0xffffffff,
0x03006419,
0x7882540d,
0xffffffff,
0xffffffff,
0x5b489014,
0x7d87ffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x6f713415,
0x22a666ce,
0x436bfc14,
0x0f006814,
0x7a833c0d,
0x08045014,
0x4c4e9fff,
0xffffffff,
0xffffffff,
0xffffffff,
0x2864c801,
0xffffffff,
0x5f15fc26,
0x39a74ece,
0xffffffff,
0x073a5000,
0x05665014,
0xffffffff,
0x2710681a,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x6a7ffc00,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x67132815,
0xffffffff,
0xffffffff,
0xffffffff,
0x04605014,
0x1ca669d5,
0xffffffff,
0xffffffff,
0x4b4e9bff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x08145014,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x8075ffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x4e4ffc26,
0xffffffff,
0x3350b02c,
0x3fa6a275,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x5449fc1e,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x5962c7ff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0xffffffff,
0x1aa651d4,
0xffffffff
};

#define fold_hashkey(k)	(((((k)<<16)-(k))<<5)%721)

