<?php

namespace Database\Seeders;


use App\Models\Courier;
use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;

class CourierSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run(): void
    {
        Courier::insert([
        ['code' => 'jne','title' => 'Jalur Nugraha Ekakurir(JNE)'],
        ['code' => 'pos','title' => 'Pos Indonesia'],
        ['code' => 'tiki','title' => 'Cita van Titipan Kilat']
        ]);
    }
}