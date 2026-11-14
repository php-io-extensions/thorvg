PHP_ARG_ENABLE([thorvg],
  [whether to enable thorvg support],
  [AS_HELP_STRING([--enable-thorvg], [Enable the ThorVG 1.1.3 bindings])],
  [no])

if test "$PHP_THORVG" != "no"; then
  PHP_REQUIRE_CXX()

  dnl The binding's own C.
  THORVG_GLUE="src/thorvg.c src/runtime.c src/canvas.c src/paint.c src/shape.c src/gradient.c src/picture.c src/misc.c"

  dnl ThorVG 1.1.3, the sources its meson.build compiles for this module choice (see
  dnl src/thorvg-config/config.h). lib/thorvg is never edited; the Lottie loader, the GPU
  dnl engines, the external-library loaders and the web media backend are not vendored.
  THORVG_LIB=" \
    lib/thorvg/src/bindings/capi/tvgCapi.cpp \
    lib/thorvg/src/common/tvgCompressor.cpp \
    lib/thorvg/src/common/tvgMath.cpp \
    lib/thorvg/src/common/tvgStr.cpp \
    lib/thorvg/src/loaders/jpg/tvgJpgLoader.cpp \
    lib/thorvg/src/loaders/jpg/tvgJpgd.cpp \
    lib/thorvg/src/loaders/media/tvgVideo.cpp \
    lib/thorvg/src/loaders/png/tvgLodePng.cpp \
    lib/thorvg/src/loaders/png/tvgLodePngUtil.cpp \
    lib/thorvg/src/loaders/png/tvgPngLoader.cpp \
    lib/thorvg/src/loaders/raw/tvgRawLoader.cpp \
    lib/thorvg/src/loaders/sfnt/tvgOtfReader.cpp \
    lib/thorvg/src/loaders/sfnt/tvgSfntLoader.cpp \
    lib/thorvg/src/loaders/sfnt/tvgSfntReader.cpp \
    lib/thorvg/src/loaders/sfnt/tvgTtfReader.cpp \
    lib/thorvg/src/loaders/svg/tvgSvgBuilder.cpp \
    lib/thorvg/src/loaders/svg/tvgSvgCssStyle.cpp \
    lib/thorvg/src/loaders/svg/tvgSvgLoader.cpp \
    lib/thorvg/src/loaders/svg/tvgSvgPath.cpp \
    lib/thorvg/src/loaders/svg/tvgSvgUtil.cpp \
    lib/thorvg/src/loaders/svg/tvgXmlParser.cpp \
    lib/thorvg/src/loaders/webp/dec/alpha.cpp \
    lib/thorvg/src/loaders/webp/dec/buffer.cpp \
    lib/thorvg/src/loaders/webp/dec/frame.cpp \
    lib/thorvg/src/loaders/webp/dec/io.cpp \
    lib/thorvg/src/loaders/webp/dec/quant.cpp \
    lib/thorvg/src/loaders/webp/dec/tree.cpp \
    lib/thorvg/src/loaders/webp/dec/vp8.cpp \
    lib/thorvg/src/loaders/webp/dec/vp8l.cpp \
    lib/thorvg/src/loaders/webp/dec/webp.cpp \
    lib/thorvg/src/loaders/webp/dsp/alpha_processing.cpp \
    lib/thorvg/src/loaders/webp/dsp/cpu.cpp \
    lib/thorvg/src/loaders/webp/dsp/dec.cpp \
    lib/thorvg/src/loaders/webp/dsp/dec_clip_tables.cpp \
    lib/thorvg/src/loaders/webp/dsp/filters.cpp \
    lib/thorvg/src/loaders/webp/dsp/lossless.cpp \
    lib/thorvg/src/loaders/webp/dsp/upsampling.cpp \
    lib/thorvg/src/loaders/webp/dsp/yuv.cpp \
    lib/thorvg/src/loaders/webp/tvgWebpLoader.cpp \
    lib/thorvg/src/loaders/webp/utils/bit_reader.cpp \
    lib/thorvg/src/loaders/webp/utils/color_cache.cpp \
    lib/thorvg/src/loaders/webp/utils/huffman.cpp \
    lib/thorvg/src/loaders/webp/utils/quant_levels_dec.cpp \
    lib/thorvg/src/loaders/webp/utils/random.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwBlendOp.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwFill.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwImage.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwMemPool.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwPostEffect.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwRaster.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwRasterCore.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwRenderer.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwRle.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwShape.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwStroke.cpp \
    lib/thorvg/src/renderer/cpu_engine/tvgSwUtil.cpp \
    lib/thorvg/src/renderer/tvgAccessor.cpp \
    lib/thorvg/src/renderer/tvgAnimation.cpp \
    lib/thorvg/src/renderer/tvgCanvas.cpp \
    lib/thorvg/src/renderer/tvgFill.cpp \
    lib/thorvg/src/renderer/tvgInitializer.cpp \
    lib/thorvg/src/renderer/tvgLoaderMgr.cpp \
    lib/thorvg/src/renderer/tvgPaint.cpp \
    lib/thorvg/src/renderer/tvgPicture.cpp \
    lib/thorvg/src/renderer/tvgRender.cpp \
    lib/thorvg/src/renderer/tvgSaver.cpp \
    lib/thorvg/src/renderer/tvgScene.cpp \
    lib/thorvg/src/renderer/tvgShape.cpp \
    lib/thorvg/src/renderer/tvgTaskScheduler.cpp \
    lib/thorvg/src/renderer/tvgText.cpp \
    lib/thorvg/src/savers/gif/tvgGifEncoder.cpp \
    lib/thorvg/src/savers/gif/tvgGifSaver.cpp \
"
  THORVG_SIMD_SRC=lib/thorvg/src/renderer/cpu_engine/tvgSwRasterSimd.cpp
  THORVG_MM=""

  dnl Media: AVFoundation on macOS (Objective-C++), meson's fallback factory elsewhere.
  dnl SIMD as meson picks it: NEON on 64-bit ARM, AVX2 (that one file only) on x86-64.
  THORVG_DEFS="-DTVG_STATIC"
  THORVG_SIMD_FLAGS=""
  case $host_os in
    darwin*) THORVG_MM="lib/thorvg/src/loaders/media/apple/tvgAvfMediaLoader.mm" ;;
    *) THORVG_LIB="$THORVG_LIB lib/thorvg/src/loaders/media/tvgMediaLoader.cpp" ;;
  esac
  case $host_cpu in
    aarch64*|arm64*) THORVG_DEFS="$THORVG_DEFS -DTHORVG_NEON_SUPPORT=1" ;;
    x86_64*|amd64*) THORVG_DEFS="$THORVG_DEFS -DTHORVG_AVX_SUPPORT=1"; THORVG_SIMD_FLAGS="-mavx2" ;;
    *) THORVG_SIMD_SRC="" ;;
  esac

  PHP_NEW_EXTENSION([thorvg], [$THORVG_GLUE], [$ext_shared],, [-std=gnu17 -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -I$ext_srcdir/lib/thorvg/src/bindings/capi])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])

  dnl ThorVG's own sources: written the way PHP_ADD_SOURCES_X writes a rule, but without
  dnl $(COMMON_FLAGS), so PHP's include paths (and its config.h) never reach them and
  dnl ThorVG's '#include "config.h"' finds src/thorvg-config/config.h.
  case $ext_dir in
    "") thorvg_srcdir="$abs_srcdir/"; thorvg_bdir="" ;;
    *) thorvg_srcdir="$abs_srcdir/$ext_dir/"; thorvg_bdir="$ext_dir/" ;;
  esac
  thorvg_inc="-I${thorvg_srcdir}src/thorvg-config -I${thorvg_srcdir}lib/thorvg/inc"
  for thorvg_dir in common renderer renderer/cpu_engine bindings/capi savers/gif \
      loaders/raw loaders/svg loaders/png loaders/jpg loaders/webp loaders/sfnt loaders/media loaders/media/apple; do
    thorvg_inc="$thorvg_inc -I${thorvg_srcdir}lib/thorvg/src/$thorvg_dir"
  done
  dnl meson's flags for a non-MSVC build (src/meson.build), C++14, optimised, quiet.
  thorvg_cxx="$shared_cxx_pre $thorvg_inc \$(CXXFLAGS_CLEAN) $pic_setting $THORVG_DEFS -std=c++14 -O3 -DNDEBUG -fvisibility=hidden -fno-exceptions -fno-rtti -fno-stack-protector -fno-math-errno -fno-unwind-tables -fno-asynchronous-unwind-tables -w"
  if test "$ext_shared" != "yes"; then
    thorvg_cxx="$php_cxx_pre $thorvg_inc \$(CXXFLAGS_CLEAN) $THORVG_DEFS -std=c++14 -O3 -DNDEBUG -fvisibility=hidden -fno-exceptions -fno-rtti -fno-stack-protector -fno-math-errno -fno-unwind-tables -fno-asynchronous-unwind-tables -w"
  fi

  thorvg_rule() {
    thorvg_obj=$thorvg_bdir$(echo "$1" | $SED -e 's/\.[[a-z]]*$//')
    if test "$ext_shared" = "yes"; then
      shared_objects_thorvg="$shared_objects_thorvg $thorvg_obj.lo"
    else
      PHP_GLOBAL_OBJS="$PHP_GLOBAL_OBJS $thorvg_obj.lo"
    fi
    cat >>Makefile.objects<<EOF
-include $thorvg_obj.dep
$thorvg_obj.lo: $thorvg_srcdir$1
	$thorvg_cxx $2 -c $thorvg_srcdir$1 -o $thorvg_obj.lo -MMD -MF $thorvg_obj.dep -MT $thorvg_obj.lo
EOF
  }

  for thorvg_src in $THORVG_LIB; do
    PHP_ADD_BUILD_DIR([$ext_builddir/$(dirname $thorvg_src)])
    thorvg_rule "$thorvg_src" ""
  done
  if test -n "$THORVG_SIMD_SRC"; then
    thorvg_rule "$THORVG_SIMD_SRC" "$THORVG_SIMD_FLAGS"
  fi
  for thorvg_src in $THORVG_MM; do
    PHP_ADD_BUILD_DIR([$ext_builddir/$(dirname $thorvg_src)])
    thorvg_rule "$thorvg_src" "-x objective-c++ -fno-objc-arc"
  done

  dnl Export get_module only (ext-pixman's lesson): another ThorVG in the process can
  dnl neither take this binding's calls nor be taken by them.
  case $host_os in
    darwin*)
      THORVG_SHARED_LIBADD="-Wl,-exported_symbol,_get_module -lc++ -framework AVFoundation -framework CoreVideo -framework CoreMedia -framework Foundation -framework CoreFoundation"
      ;;
    *)
      THORVG_SHARED_LIBADD="-Wl,--version-script=$ext_srcdir/src/thorvg.map -lstdc++"
      PHP_ADD_LIBRARY([pthread],, [THORVG_SHARED_LIBADD])
      PHP_ADD_LIBRARY([m],, [THORVG_SHARED_LIBADD])
      ;;
  esac
  PHP_SUBST([THORVG_SHARED_LIBADD])
fi
