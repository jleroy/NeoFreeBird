// Experimental fallback for embedded login: request the method-selection route.
// Keep the current route suffix; X may require a different server-issued route
// ID or state transition, so this must be validated against the live flow.
(() => {
    'use strict';
    if (location.hostname !== 'x.com' || window.__nfbLogin2FAInstalled) return;
    window.__nfbLogin2FAInstalled = true;

    // Try each source route only once per document. If X rejects the transition
    // and returns to it, leave the page available for inspection, without a loop.
    const attemptedRoutes = new Set();
    function check() {
        if (location.pathname !== '/i/jf/onboarding/web' ||
            !/^#\/s\/passkey_2fa_auth(?:\/|$)/.test(location.hash)) return;
        const source = location.href;
        if (attemptedRoutes.has(source)) return;
        attemptedRoutes.add(source);
        location.replace(source.replace('#/s/passkey_2fa_auth', '#/s/two_factor_method'));
    }

    window.addEventListener('hashchange', check);
    // X can also update the route via pushState/replaceState, without hashchange.
    window.setInterval(check, 500);
    check();
})();
