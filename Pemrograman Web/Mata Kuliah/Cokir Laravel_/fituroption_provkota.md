# Update

Tambah dan edit pada file berikut:

- app\Http\Controllers\CityController.php ( **Buat Baru** )
- resources\js\ongkir.js ( **Update** )
- routes\web.php ( **Update** )
- resources\views\layouts\app.blade.php ( **Update** )

## Instruksi

**CityController.php**

```php
<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\City;

class CityController extends Controller
{
    public function getCities($province_id)
    {
        $cities = City::where('province_code', $province_id)->pluck('title', 'code');

        return response()->json($cities);
    }
}

```
**web.php**

```php
<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\HomeController;
use App\Http\Controllers\CityController;


/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    // return view('welcome'); ganti dengan yang baru      
    return view('home');   
});

Route::get('/', [HomeController::class, 'index']);

Route::get('/get-cities/{province_id}', [CityController::class, 'getCities']);

```


**ongkir.js**
```javascript
$(document).ready(function () {
    $('select[name="origin_province"]').on('change', function () {
        var provinceId = $(this).val();
        if (provinceId) {
            $.ajax({
                url: '/get-cities/' + provinceId,
                type: 'GET',
                dataType: 'json',
                success: function (data) {
                    $('select[name="origin_city"]').empty();

                    $.each(data, function (key, value) {
                        $('select[name="origin_city"]').append('<option value="' + key + '">' + value + '</option>');
                    });
                }
            });
        } else {
            $('select[name="origin_city"]').empty();
        }
    });
});
```
**app.blade.php** 

```html
<!doctype html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- CSRF Token -->
    <meta name="csrf-token" content="{{ csrf_token() }}">

    <title>{{ config('app.name', 'Laravel') }}</title>

    <!-- Scripts -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.13.1/js/all.min.js"></script>
    <script src="https://code.jquery.com/jquery-3.6.4.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js"></script>
    <script src="/js/app.js"></script>
    <script src="/js/ongkir.js"></script>

    <!-- Fonts -->
    <link rel="dns-prefetch" href="//fonts.gstatic.com">
    <link href="https://fonts.googleapis.com/css?family=Nunito" rel="stylesheet">

    <!-- Styles -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css" rel="stylesheet">
    <style>
        .ongkir-header {
            padding: 3rem 1.5rem;
            text-align: center;
        }

        h1 {
            color: #BEB3A6;
            font-weight: 500;
            line-height: 1.2;
        }
        p {
            color: #BEB3A6;
        }
        .row {
            margin-bottom: 20px;
        }
    </style>
</head>
<body>
    <main class="vstack gap-1">
        @yield('content')
    </main>
</body>
</html>
```


# Video Instruksi



https://github.com/miezlearning/Kuliah/assets/129609799/cc6c4800-982a-4ca2-b0a1-62683fd568ce




## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
