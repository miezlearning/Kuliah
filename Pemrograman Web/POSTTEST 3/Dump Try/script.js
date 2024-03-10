const modeToggle = document.getElementById("mode-toggle");
        const body = document.body;

        modeToggle.addEventListener("click", function () {
            body.classList.toggle("dark-mode");
            body.classList.toggle("light-mode");
        });