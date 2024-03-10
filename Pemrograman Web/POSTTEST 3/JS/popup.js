//   POPUP
$(document).ready(function() {
    const popup = $('#popup');

if (localStorage.getItem('popupShown') !== 'true') {
    popup.css('display', 'block');
    localStorage.setItem('popupShown', 'true');
}

$('#close-popup').on('click', function() {
    popup.css('display', 'none');
});
});