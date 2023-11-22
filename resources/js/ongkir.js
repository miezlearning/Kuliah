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