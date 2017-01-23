#include "Gfx_1.3.h"

CSettings::CSettings() :
card_id(0),
res_x(640),
scr_res_x(640),
res_y(480),
scr_res_y(480),
#ifndef ANDROID
res_data(GR_RESOLUTION_640x480),
res_data_org(GR_RESOLUTION_640x480),
#endif
advanced_options(0),
texenh_options(0),
ssformat(0),
vsync(0),

clock(0),
clock_24_hr(0),
rotate(0),

filtering(0),
fog(0),
buff_clear(0),
swapmode(0),
lodmode(0),
aspectmode(0),
use_hotkeys(0),
#ifdef TEXTURE_FILTER
//Texture filtering options
texture_dir(""),
ghq_fltr(0),
ghq_enht(0),
ghq_cmpr(0),
ghq_hirs(0),
ghq_use(0),
ghq_enht_cmpr(0),
ghq_enht_tile(0),
ghq_enht_f16bpp(0),
ghq_enht_gz(0),
ghq_enht_nobg(0),
ghq_hirs_cmpr(0),
ghq_hirs_tile(0),
ghq_hirs_f16bpp(0),
ghq_hirs_gz(0),
ghq_hirs_altcrc(0),
ghq_cache_save(0),
ghq_cache_size(0),
ghq_hirs_let_texartists_fly(0),
ghq_hirs_dump(0),
#endif
autodetect_ucode(0),
ucode(0),
logging(0),
elogging(0),
log_clear(0),
run_in_window(0),
filter_cache(0),
unk_as_red(0),
log_unk(0),
unk_clear(0),
wireframe(0),
wfmode(0),

// Special fixes
offset_x(0),
offset_y(0),
scale_x(0),
scale_y(0),
fast_crc(0),
alt_tex_size(0),
use_sts1_only(0),
flame_corona(0), //hack for zeldas flame's corona
increase_texrect_edge(0), // add 1 to lower right corner coordinates of texrect
decrease_fillrect_edge(0), // sub 1 from lower right corner coordinates of fillrect
texture_correction(0), // enable perspective texture correction emulation. is on by default
stipple_mode(0), //used for dithered alpha emulation
stipple_pattern(0), //used for dithered alpha emulation
force_microcheck(0), //check microcode each frame, for mixed F3DEX-S2DEX games
force_quad3d(0), //force 0xb5 command to be quad, not line 3d
clip_zmin(0), //enable near z clipping
clip_zmax(0), //enable far plane clipping;
adjust_aspect(0), //adjust screen aspect for wide screen mode
force_calc_sphere(0), //use spheric mapping only, Ridge Racer 64
pal230(0),    //set special scale for PAL games
correct_viewport(0), //correct viewport values
zmode_compare_less(0), //force GR_CMP_LESS for zmode=0 (opaque)and zmode=1 (interpenetrating)
old_style_adither(0), //apply alpha dither regardless of alpha_dither_mode
n64_z_scale(0), //scale vertex z value before writing to depth buffer, as N64 does.

hacks(0),

//wrapper settings
#ifndef ANDROID
wrpResolution(0),
#endif
wrpVRAM(0),
wrpFBO(0),
wrpAnisotropic(0)
{
}

void ReadSettings()
{
    g_settings->card_id = GetSetting(Set_CardId);
#ifdef ANDROID
    g_settings->scr_res_x = g_settings->res_x = g_width;
    g_settings->scr_res_y = g_settings->res_y = g_height;
#else
    g_settings->res_data = (uint32_t)GetSetting(Set_Resolution);
    if (g_settings->res_data >= 24) g_settings->res_data = 12;
    g_settings->scr_res_x = g_settings->res_x = resolutions[g_settings->res_data][0];
    g_settings->scr_res_y = g_settings->res_y = resolutions[g_settings->res_data][1];
    g_settings->wrpResolution = GetSetting(Set_wrpResolution);
#endif
    g_settings->vsync = GetSetting(Set_vsync);
    g_settings->ssformat = (uint8_t)GetSetting(Set_ssformat);
    g_settings->clock = GetSetting(Set_clock);
    g_settings->clock_24_hr = GetSetting(Set_clock_24_hr);
    g_settings->rotate = GetSetting(Set_Rotate);
    g_settings->advanced_options = Set_basic_mode ? !GetSystemSetting(Set_basic_mode) : 0;
    g_settings->texenh_options = GetSetting(Set_texenh_options);
    g_settings->use_hotkeys = GetSetting(Set_hotkeys);

    g_settings->wrpVRAM = GetSetting(Set_wrpVRAM);
    g_settings->wrpFBO = GetSetting(Set_wrpFBO);
    g_settings->wrpAnisotropic = GetSetting(Set_wrpAnisotropic);

#ifndef _ENDUSER_RELEASE_
    g_settings->autodetect_ucode = GetSetting(Set_autodetect_ucode);
    g_settings->ucode = GetSetting(Set_ucode);
    g_settings->wireframe = GetSetting(Set_wireframe);
    g_settings->wfmode = GetSetting(Set_wfmode);
    g_settings->logging = GetSetting(Set_logging);
    g_settings->log_clear = GetSetting(Set_log_clear);
    g_settings->run_in_window = GetSetting(Set_run_in_window);
    g_settings->elogging = GetSetting(Set_elogging);
    g_settings->filter_cache = GetSetting(Set_filter_cache);
    g_settings->unk_as_red = GetSetting(Set_unk_as_red);
    g_settings->log_unk = GetSetting(Set_log_unk);
    g_settings->unk_clear = GetSetting(Set_unk_clear);
#else
    g_settings->autodetect_ucode = TRUE;
    g_settings->ucode = 2;
    g_settings->wireframe = FALSE;
    g_settings->wfmode = 0;
    g_settings->logging = FALSE;
    g_settings->log_clear = FALSE;
    g_settings->run_in_window = FALSE;
    g_settings->elogging = FALSE;
    g_settings->filter_cache = FALSE;
    g_settings->unk_as_red = FALSE;
    g_settings->log_unk = FALSE;
    g_settings->unk_clear = FALSE;
#endif

#ifdef TEXTURE_FILTER
    char texture_dir[260];
    memset(texture_dir, 0, sizeof(texture_dir));
    GetSystemSettingSz(Set_texture_dir, texture_dir, sizeof(texture_dir));
    g_settings->texture_dir = texture_dir;
    g_settings->ghq_fltr = (uint8_t)GetSetting(Set_ghq_fltr);
    g_settings->ghq_cmpr = (uint8_t)GetSetting(Set_ghq_cmpr);
    g_settings->ghq_enht = (uint8_t)GetSetting(Set_ghq_enht);
    g_settings->ghq_hirs = (uint8_t)GetSetting(Set_ghq_hirs);
    g_settings->ghq_enht_cmpr = GetSetting(Set_ghq_enht_cmpr);
    g_settings->ghq_enht_tile = GetSetting(Set_ghq_enht_tile);
    g_settings->ghq_enht_f16bpp = GetSetting(Set_ghq_enht_f16bpp);
    g_settings->ghq_enht_gz = GetSetting(Set_ghq_enht_gz);
    g_settings->ghq_enht_nobg = GetSetting(Set_ghq_enht_nobg);
    g_settings->ghq_hirs_cmpr = GetSetting(Set_ghq_hirs_cmpr);
    g_settings->ghq_hirs_tile = GetSetting(Set_ghq_hirs_tile);
    g_settings->ghq_hirs_f16bpp = GetSetting(Set_ghq_hirs_f16bpp);
    g_settings->ghq_hirs_gz = GetSetting(Set_ghq_hirs_gz);
    g_settings->ghq_hirs_altcrc = GetSetting(Set_ghq_hirs_altcrc);
    g_settings->ghq_cache_save = GetSetting(Set_ghq_cache_save);
    g_settings->ghq_cache_size = GetSetting(Set_ghq_cache_size);
    g_settings->ghq_hirs_let_texartists_fly = GetSetting(Set_ghq_hirs_let_texartists_fly);
    g_settings->ghq_hirs_dump = GetSetting(Set_ghq_hirs_dump);
#endif
}

void ReadSpecialSettings(const char * name)
{
    g_settings->hacks = 0;

    //detect games which require special hacks
    if (strstr(name, (const char *)"ZELDA"))
        g_settings->hacks |= (hack_Zelda | hack_OoT);
    else if (strstr(name, (const char *)"MASK"))
        g_settings->hacks |= hack_Zelda;
    else if (strstr(name, (const char *)"ROADSTERS TROPHY"))
        g_settings->hacks |= hack_Zelda;
    else if (strstr(name, (const char *)"Diddy Kong Racing"))
        g_settings->hacks |= hack_Diddy;
    else if (strstr(name, (const char *)"Tonic Trouble"))
        g_settings->hacks |= hack_Tonic;
    else if (strstr(name, (const char *)"All") && strstr(name, (const char *)"Star") && strstr(name, (const char *)"Baseball"))
        g_settings->hacks |= hack_ASB;
    else if (strstr(name, (const char *)"Beetle") || strstr(name, (const char *)"BEETLE") || strstr(name, (const char *)"HSV"))
        g_settings->hacks |= hack_BAR;
    else if (strstr(name, (const char *)"I S S 64") || strstr(name, (const char *)"J WORLD SOCCER3") || strstr(name, (const char *)"PERFECT STRIKER") || strstr(name, (const char *)"RONALDINHO SOCCER"))
        g_settings->hacks |= hack_ISS64;
    else if (strstr(name, (const char *)"MARIOKART64"))
        g_settings->hacks |= hack_MK64;
    else if (strstr(name, (const char *)"NITRO64"))
        g_settings->hacks |= hack_WCWnitro;
    else if (strstr(name, (const char *)"CHOPPER_ATTACK") || strstr(name, (const char *)"WILD CHOPPERS"))
        g_settings->hacks |= hack_Chopper;
    else if (strstr(name, (const char *)"Resident Evil II") || strstr(name, (const char *)"BioHazard II"))
        g_settings->hacks |= hack_RE2;
    else if (strstr(name, (const char *)"YOSHI STORY"))
        g_settings->hacks |= hack_Yoshi;
    else if (strstr(name, (const char *)"F-Zero X") || strstr(name, (const char *)"F-ZERO X"))
        g_settings->hacks |= hack_Fzero;
    else if (strstr(name, (const char *)"PAPER MARIO") || strstr(name, (const char *)"MARIO STORY"))
        g_settings->hacks |= hack_PMario;
    else if (strstr(name, (const char *)"TOP GEAR RALLY 2"))
        g_settings->hacks |= hack_TGR2;
    else if (strstr(name, (const char *)"TOP GEAR RALLY"))
        g_settings->hacks |= hack_TGR;
    else if (strstr(name, (const char *)"Top Gear Hyper Bike"))
        g_settings->hacks |= hack_Hyperbike;
    else if (strstr(name, (const char *)"Killer Instinct Gold") || strstr(name, (const char *)"KILLER INSTINCT GOLD"))
        g_settings->hacks |= hack_KI;
    else if (strstr(name, (const char *)"Knockout Kings 2000"))
        g_settings->hacks |= hack_Knockout;
    else if (strstr(name, (const char *)"LEGORacers"))
        g_settings->hacks |= hack_Lego;
    else if (strstr(name, (const char *)"OgreBattle64"))
        g_settings->hacks |= hack_Ogre64;
    else if (strstr(name, (const char *)"Pilot Wings64"))
        g_settings->hacks |= hack_Pilotwings;
    else if (strstr(name, (const char *)"Supercross"))
        g_settings->hacks |= hack_Supercross;
    else if (strstr(name, (const char *)"STARCRAFT 64"))
        g_settings->hacks |= hack_Starcraft;
    else if (strstr(name, (const char *)"BANJO KAZOOIE 2") || strstr(name, (const char *)"BANJO TOOIE"))
        g_settings->hacks |= hack_Banjo2;
    else if (strstr(name, (const char *)"FIFA: RTWC 98") || strstr(name, (const char *)"RoadToWorldCup98"))
        g_settings->hacks |= hack_Fifa98;
    else if (strstr(name, (const char *)"Mega Man 64") || strstr(name, (const char *)"RockMan Dash"))
        g_settings->hacks |= hack_Megaman;
    else if (strstr(name, (const char *)"MISCHIEF MAKERS") || strstr(name, (const char *)"TROUBLE MAKERS"))
        g_settings->hacks |= hack_Makers;
    else if (strstr(name, (const char *)"GOLDENEYE"))
        g_settings->hacks |= hack_GoldenEye;
    else if (strstr(name, (const char *)"PUZZLE LEAGUE"))
        g_settings->hacks |= hack_PPL;
	else if (strstr(name, (const char *)"WIN BACK") || strstr(name, (const char *)"OPERATION WINBACK"))
		g_settings->hacks |= hack_Winback;

    g_settings->alt_tex_size = GetSetting(Set_alt_tex_size);
    g_settings->use_sts1_only = GetSetting(Set_use_sts1_only);
    g_settings->force_calc_sphere = GetSetting(Set_force_calc_sphere);
    g_settings->correct_viewport = GetSetting(Set_correct_viewport);
    g_settings->increase_texrect_edge = GetSetting(Set_increase_texrect_edge);
    g_settings->decrease_fillrect_edge = GetSetting(Set_decrease_fillrect_edge);
    g_settings->texture_correction = GetSetting(Set_texture_correction) == 0 ? 0 : 1;
    g_settings->pal230 = GetSetting(Set_pal230) == 1 ? 1 : 0;
    g_settings->stipple_mode = GetSetting(Set_stipple_mode);
    int stipple_pattern = GetSetting(Set_stipple_pattern);
    g_settings->stipple_pattern = stipple_pattern > 0 ? (uint32_t)stipple_pattern : 0x3E0F83E0;
    g_settings->force_microcheck = GetSetting(Set_force_microcheck);
    g_settings->force_quad3d = GetSetting(Set_force_quad3d);
    g_settings->clip_zmin = GetSetting(Set_clip_zmin);
    g_settings->clip_zmax = GetSetting(Set_clip_zmax);
    g_settings->fast_crc = GetSetting(Set_fast_crc);
    g_settings->adjust_aspect = GetSetting(Set_adjust_aspect);
    g_settings->zmode_compare_less = GetSetting(Set_zmode_compare_less);
    g_settings->old_style_adither = GetSetting(Set_old_style_adither);
    g_settings->n64_z_scale = GetSetting(Set_n64_z_scale);

    //frame buffer
    int optimize_texrect = GetSetting(g_romopen ? Set_optimize_texrect : Set_optimize_texrect_default);
    int ignore_aux_copy = GetSetting(Set_ignore_aux_copy);
    int hires_buf_clear = GetSetting(Set_hires_buf_clear);
    int read_alpha = GetSetting(Set_fb_read_alpha);
    int useless_is_useless = GetSetting(Set_useless_is_useless);
    int fb_crc_mode = GetSetting(Set_fb_crc_mode);

    if (optimize_texrect > 0) g_settings->frame_buffer |= fb_optimize_texrect;
    else if (optimize_texrect == 0) g_settings->frame_buffer &= ~fb_optimize_texrect;
    if (ignore_aux_copy > 0) g_settings->frame_buffer |= fb_ignore_aux_copy;
    else if (ignore_aux_copy == 0) g_settings->frame_buffer &= ~fb_ignore_aux_copy;
    if (hires_buf_clear > 0) g_settings->frame_buffer |= fb_hwfbe_buf_clear;
    else if (hires_buf_clear == 0) g_settings->frame_buffer &= ~fb_hwfbe_buf_clear;
    if (read_alpha > 0) g_settings->frame_buffer |= fb_read_alpha;
    else if (read_alpha == 0) g_settings->frame_buffer &= ~fb_read_alpha;
    if (useless_is_useless > 0) g_settings->frame_buffer |= fb_useless_is_useless;
    else g_settings->frame_buffer &= ~fb_useless_is_useless;
    if (fb_crc_mode >= 0) g_settings->fb_crc_mode = (CSettings::FBCRCMODE)fb_crc_mode;

    g_settings->filtering = GetSetting(g_romopen ? Set_filtering : Set_filtering_default);
    g_settings->fog = GetSetting(g_romopen ? Set_fog : Set_fog_default);
    g_settings->buff_clear = GetSetting(g_romopen ? Set_buff_clear : Set_buff_clear_default);
    g_settings->swapmode = GetSetting(g_romopen ? Set_swapmode : Set_swapmode_default);
    g_settings->aspectmode = GetSetting(g_romopen ? Set_aspect : Set_aspect_default);
    g_settings->lodmode = GetSetting(g_romopen ? Set_lodmode : Set_lodmode_default);
#ifdef _WIN32
    g_settings->res_data = GetSetting(Set_Resolution);
    if (g_settings->res_data < 0 || g_settings->res_data >= 0x18) g_settings->res_data = 12;
    g_settings->scr_res_x = g_settings->res_x = resolutions[g_settings->res_data][0];
    g_settings->scr_res_y = g_settings->res_y = resolutions[g_settings->res_data][1];
#endif

    //frame buffer
    int smart_read = GetSetting(g_romopen ? Set_fb_smart : Set_fb_smart_default);
    int hires = GetSetting(g_romopen ? Set_fb_hires : Set_fb_hires_default);
    int read_always = GetSetting(g_romopen ? Set_fb_read_always : Set_fb_read_always_default);
    int read_back_to_screen = GetSetting(g_romopen ? Set_read_back_to_screen : Set_read_back_to_screen_default);
    int cpu_write_hack = GetSetting(g_romopen ? Set_detect_cpu_write : Set_detect_cpu_write_default);
    int get_fbinfo = GetSetting(g_romopen ? Set_fb_get_info : Set_fb_get_info_default);
    int depth_render = GetSetting(g_romopen ? Set_fb_render : Set_fb_render_default);

    if (smart_read > 0) g_settings->frame_buffer |= fb_emulation;
    else if (smart_read == 0) g_settings->frame_buffer &= ~fb_emulation;
    if (hires > 0) g_settings->frame_buffer |= fb_hwfbe;
    else if (hires == 0) g_settings->frame_buffer &= ~fb_hwfbe;
    if (read_always > 0) g_settings->frame_buffer |= fb_ref;
    else if (read_always == 0) g_settings->frame_buffer &= ~fb_ref;
    if (read_back_to_screen == 1) g_settings->frame_buffer |= fb_read_back_to_screen;
    else if (read_back_to_screen == 2) g_settings->frame_buffer |= fb_read_back_to_screen2;
    else if (read_back_to_screen == 0) g_settings->frame_buffer &= ~(fb_read_back_to_screen | fb_read_back_to_screen2);
    if (cpu_write_hack > 0) g_settings->frame_buffer |= fb_cpu_write_hack;
    else if (cpu_write_hack == 0) g_settings->frame_buffer &= ~fb_cpu_write_hack;
    if (get_fbinfo > 0) g_settings->frame_buffer |= fb_get_info;
    else if (get_fbinfo == 0) g_settings->frame_buffer &= ~fb_get_info;
    if (depth_render > 0) g_settings->frame_buffer |= fb_depth_render;
    else if (depth_render == 0) g_settings->frame_buffer &= ~fb_depth_render;
    g_settings->frame_buffer |= fb_motionblur;
    g_settings->flame_corona = (g_settings->hacks & hack_Zelda) && !fb_depth_render_enabled;
}

void WriteSettings(void)
{
    SetSetting(Set_CardId, g_settings->card_id);
#ifdef _WIN32
    SetSetting(Set_Resolution, (int)g_settings->res_data);
    SetSetting(Set_wrpResolution, g_settings->wrpResolution);
#endif
    SetSetting(Set_ssformat, g_settings->ssformat);
    SetSetting(Set_vsync, g_settings->vsync);
    SetSetting(Set_clock, g_settings->clock);
    SetSetting(Set_clock_24_hr, g_settings->clock_24_hr);
    SetSetting(Set_Rotate, g_settings->rotate);
    //SetSetting(Set_advanced_options,g_settings->advanced_options);
    SetSetting(Set_texenh_options, g_settings->texenh_options);

    SetSetting(Set_wrpVRAM, g_settings->wrpVRAM);
    SetSetting(Set_wrpFBO, g_settings->wrpFBO);
    SetSetting(Set_wrpAnisotropic, g_settings->wrpAnisotropic);

#ifndef _ENDUSER_RELEASE_
    SetSetting(Set_autodetect_ucode, g_settings->autodetect_ucode);
    SetSetting(Set_ucode, (int)g_settings->ucode);
    SetSetting(Set_wireframe, g_settings->wireframe);
    SetSetting(Set_wfmode, g_settings->wfmode);
    SetSetting(Set_logging, g_settings->logging);
    SetSetting(Set_log_clear, g_settings->log_clear);
    SetSetting(Set_run_in_window,g_settings->run_in_window);
    SetSetting(Set_elogging,g_settings->elogging);
    SetSetting(Set_filter_cache,g_settings->filter_cache);
    SetSetting(Set_unk_as_red,g_settings->unk_as_red);
    SetSetting(Set_log_unk,g_settings->log_unk);
    SetSetting(Set_unk_clear, g_settings->unk_clear);
#endif //_ENDUSER_RELEASE_

#ifdef TEXTURE_FILTER
    SetSetting(Set_ghq_fltr, g_settings->ghq_fltr);
    SetSetting(Set_ghq_cmpr, g_settings->ghq_cmpr);
    SetSetting(Set_ghq_enht, g_settings->ghq_enht);
    SetSetting(Set_ghq_hirs, g_settings->ghq_hirs);
    SetSetting(Set_ghq_enht_cmpr, g_settings->ghq_enht_cmpr);
    SetSetting(Set_ghq_enht_tile, g_settings->ghq_enht_tile);
    SetSetting(Set_ghq_enht_f16bpp, g_settings->ghq_enht_f16bpp);
    SetSetting(Set_ghq_enht_gz, g_settings->ghq_enht_gz);
    SetSetting(Set_ghq_enht_nobg, g_settings->ghq_enht_nobg);
    SetSetting(Set_ghq_hirs_cmpr, g_settings->ghq_hirs_cmpr);
    SetSetting(Set_ghq_hirs_tile, g_settings->ghq_hirs_tile);
    SetSetting(Set_ghq_hirs_f16bpp, g_settings->ghq_hirs_f16bpp);
    SetSetting(Set_ghq_hirs_gz, g_settings->ghq_hirs_gz);
    SetSetting(Set_ghq_hirs_altcrc, g_settings->ghq_hirs_altcrc);
    SetSetting(Set_ghq_cache_save, g_settings->ghq_cache_save);
    SetSetting(Set_ghq_cache_size, g_settings->ghq_cache_size);
    SetSetting(Set_ghq_hirs_let_texartists_fly, g_settings->ghq_hirs_let_texartists_fly);
    SetSetting(Set_ghq_hirs_dump, g_settings->ghq_hirs_dump);
#endif

    SetSetting(g_romopen ? Set_filtering : Set_filtering_default, g_settings->filtering);
    SetSetting(g_romopen ? Set_fog : Set_fog_default, g_settings->fog);
    SetSetting(g_romopen ? Set_buff_clear : Set_buff_clear_default, g_settings->buff_clear);
    SetSetting(g_romopen ? Set_swapmode : Set_swapmode_default, g_settings->swapmode);
    SetSetting(g_romopen ? Set_lodmode : Set_lodmode_default, g_settings->lodmode);
    SetSetting(g_romopen ? Set_aspect : Set_aspect_default, g_settings->aspectmode);

    SetSetting(g_romopen ? Set_fb_read_always : Set_fb_read_always_default, g_settings->frame_buffer&fb_ref ? 1 : 0);
    SetSetting(g_romopen ? Set_fb_smart : Set_fb_smart_default, g_settings->frame_buffer & fb_emulation ? 1 : 0);
    SetSetting(g_romopen ? Set_fb_hires : Set_fb_hires_default, g_settings->frame_buffer & fb_hwfbe ? 1 : 0);
    SetSetting(g_romopen ? Set_fb_get_info : Set_fb_get_info_default, g_settings->frame_buffer & fb_get_info ? 1 : 0);
    SetSetting(g_romopen ? Set_fb_render : Set_fb_render_default, g_settings->frame_buffer & fb_depth_render ? 1 : 0);
    SetSetting(g_romopen ? Set_detect_cpu_write : Set_detect_cpu_write_default, g_settings->frame_buffer & fb_cpu_write_hack ? 1 : 0);
    if (g_settings->frame_buffer & fb_read_back_to_screen)
    {
        SetSetting(g_romopen ? Set_read_back_to_screen : Set_read_back_to_screen_default, 1);
    }
    else if (g_settings->frame_buffer & fb_read_back_to_screen2)
    {
        SetSetting(g_romopen ? Set_read_back_to_screen : Set_read_back_to_screen_default, 2);
    }
    else
    {
        SetSetting(g_romopen ? Set_read_back_to_screen : Set_read_back_to_screen_default, 0);
    }

    FlushSettings();
}

