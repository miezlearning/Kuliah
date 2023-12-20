@extends('layouts.app')

@section('content')
    <div class="container">
        <div class="ongkir-header">
            <h1>CodeOngkir</h1>
            <p class="lead">
                Project Cek Ongkir ke Seluruh Koda dan Kabupaten di Indonesia
            </p>
        </div>

        <div class="row row-cols-1 row-cols-md-3 g-4">
            <div class="col">
                <div class="card h-100 text-center">
                    <div class="
            card-header">
                        <h4 class="my-0 font-weight-normal text-center">Free</h4>
                    </div>
                    <div class="card-body">
                        <i class="fas fa-truck" style="font-size:80px"></i>
                        <ul class="list-unstyled mt-3 mb-4">
                            <li>Cek Ongkir Lebih Mudah</li>
                        </ul>
                        <button type="button" class="btn btn-lg btn-block btn-outline-primary">Sign up for free</button>
                    </div>
                </div>
            </div>
            <div class="col">
                <div class="card h-100 text-center">
                    <div class="card-header">
                        <h4 class="my-0 font-weight-normal text-center">Pro</h4>
                    </div>
                    <div class="card-body">
                        <i class="fas fa-box" style="font-size:80px"></i>
                        <ul class="list-unstyled mt-3 mb-4">
                            <li>Lacak lokasi paket</li>
                        </ul>
                        <button type="button" class="btn btn-lg btn-block btn-primary">Get started</button>
                    </div>
                </div>
            </div>
            <div class="col">
                <div class="card h-100 text-center">
                    <div class="card-header">
                        <h4 class="my-0 font-weight-normal text-center">Enterprise</h4>
                    </div>
                    <div class="card-body">
                        <i class="fas fa-plane-departure" style="font-size:80px"></i>
                        <ul class="list-unstyled mt-3 mb-4">
                            <li>Cek Ongkir Pengiriman Internasional</li>
                        </ul>
                        <button type="button" class="btn btn-lg btn-block btn-primary">Contact us</button>
                    </div>
                </div>
            </div>
        </div>

        <div class="card mb-4 shadow-sm">
            <div class="card-header">
                <h4 class="my-0 font-weight-normal">Formulir Cek Ongkir</h4>
            </div>
            <div class="card-body">
                <form action="{{ route('store') }}" method="POST">
                    @csrf
                    <div class="form-row">
                        <div class="col">
                            <h5 class="text-muted">Asal Pengirim:</h5>
                            <div class="form-group">
                                <label for="">Provinsi</label>
                                <select name="origin_province" id="" class="form-control">
                                    <option value="#">-</option>
                                    @foreach ($province as $code => $title)
                                        <option value="{{ $code }}">{{ $title }}</option>
                                    @endforeach
                                </select>
                            </div>
                            <div class="form-group">
                                <label for="">Kota/Kabupaten</label>
                                <select name="origin_city" id="" class="form-control">
                                    <option value="#">-</option>
                                </select>
                            </div>
                            <h5 class="text-muted">Tujuan Pengirim:</h5>
                            <div class="form-group">
                                <label for="">Kota/Kabupaten</label>
                                <select name="destination_city" id="destination_city" class="form-control">
                                    <option value="#">-</option>
                                    @foreach ($cities as $code => $title)
                                        <option value="{{ $code }}">{{ $title }}</option>
                                    @endforeach
                                </select>

                            </div>
                        </div>
                        <div class="col">
                            <h5 class="text-muted">Pilih Expedisi:</h5>
                            @foreach ($couriers as $key => $value)
                                <div class="form-check form-check-inline">
                                    <input class="form-check-input" type="checkbox" id="couriers-{{ $key }}"
                                        name="couriers[]" value="{{ $value->code }}">
                                    <label class="form-check-label"
                                        for="couriers-{{ $key }}">{{ $value->title }}</label>
                                </div>
                            @endforeach
                        </div>
                    </div>
                    <div class="form-row">
                        <div class="col">
                            <button type="submit" class="btn btn-primary">Submit</button>
                        </div>
                    </div>
                </form>
            </div>
        </div>
    @endsection