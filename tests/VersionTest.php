<?php

declare(strict_types=1);

it('reports ThorVG 1.1.3', function (): void {
    expect(tvg_engine_version($major, $minor, $micro, $version))->toBe(0)
        ->and([$major, $minor, $micro, $version])->toBe([1, 1, 3, '1.1.3']);
});

it('prints the extension version, the ThorVG version, the upstream commit and the modules', function (): void {
    ob_start();
    phpinfo(INFO_MODULES);
    $info = ob_get_clean();

    expect($info)->toContain('0.11.0')
        ->and($info)->toContain('1.1.3')
        ->and($info)->toContain('589bc4120f2097fb1b135e552c2ef39f6581612b')
        ->and($info)->toContain('svg, png, jpg, webp, ttf, otf, media, gif saver');
});
