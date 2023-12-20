const mix = require("laravel-mix");

/*
 |--------------------------------------------------------------------------
 | Mix Asset Management
 |--------------------------------------------------------------------------
 |
 | Mix provides a clean, fluent API for defining some Webpack build steps
 | for your Laravel applications. By default, we are compiling the CSS
 | file for the application as well as bundling up all the JS files.
 |
 */

mix.js(
    [
       // 'resources/js/app.js',
        "resources/js/ongkir.js",
    ],
    "public/js"
)
    .postCss("resources/css/app.css", "public/css", [
        //
    ])
    .copy("node_modules/select2/dist/css/select2.min.css", "public/css")
    .copy("node_modules/select2/dist/js/select2.min.js", "public/js");