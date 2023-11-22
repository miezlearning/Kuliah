<?php

namespace Database\Seeders;


use App\Models\Province;
use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;

class ProvinceSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run(): void
    {
        $file  = file_get_contents(base_path('/database/provinsi.json'));
        $data = json_decode($file, true);
        Province::insert($data);
    }
}