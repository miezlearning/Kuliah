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