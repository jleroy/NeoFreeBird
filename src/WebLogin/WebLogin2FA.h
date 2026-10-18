// Embedded in the tweak so login fallback does not depend on resource-pack updates.
#import <Foundation/Foundation.h>

static NSString* const kWebLogin2FAJS =
    @"// Experimental fallback for embedded login: request the method-selection route.\n"
     "// Keep the current route suffix; X may require a different server-issued route\n"
     "// ID or state transition, so this must be validated against the live flow.\n"
     "(() => {\n"
     "    'use strict';\n"
     "    if (location.hostname !== 'x.com' || window.__nfbLogin2FAInstalled) return;\n"
     "    window.__nfbLogin2FAInstalled = true;\n"
     "\n"
     "    // Try each source route only once per document. If X rejects the transition\n"
     "    // and returns to it, leave the page available for inspection, without a loop.\n"
     "    const attemptedRoutes = new Set();\n"
     "    function check() {\n"
     "        if (location.pathname !== '/i/jf/onboarding/web' ||\n"
     "            !/^#\\/s\\/passkey_2fa_auth(?:\\/|$)/.test(location.hash)) return;\n"
     "        const source = location.href;\n"
     "        if (attemptedRoutes.has(source)) return;\n"
     "        attemptedRoutes.add(source);\n"
     "        location.replace(source.replace('#/s/passkey_2fa_auth', '#/s/two_factor_method'));\n"
     "    }\n"
     "\n"
     "    window.addEventListener('hashchange', check);\n"
     "    // X can also update the route via pushState/replaceState, without hashchange.\n"
     "    window.setInterval(check, 500);\n"
     "    check();\n"
     "})();\n";
