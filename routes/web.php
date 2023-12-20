<?php

use App\Http\Controllers\CheckOngkirController;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider and all of them will
| be assigned to the "web" middleware group. Make something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});

Route::get('provinces', [CheckOngkirController::class, 'province'])->name('provinces');
Route::get('cities', [CheckOngkirController::class, 'city'])->name('cities');
Route::post('check-ongkir', [CheckOngkirController::class, 'checkOngkir'])->name('check-ongkir');