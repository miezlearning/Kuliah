<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\Relations\BelongsTo;


class City extends Model
{
    use HasFactory;
    protected $guarded = [];
    public function province(): BelongsTo
{
    return $this->belongsTo(Province::class);
}
}