document.addEventListener('DOMContentLoaded', function () { 
    let correct = document.querySelector('#correct');
    correct.addEventListener('click', function () {
        correct.style.backgroundColor = 'green';
        document.querySelector('#feedback').innerHTML = 'Correct!';
    });

    let incorrects = document.querySelectorAll('#incorrect');
    for (let i = 0; i < incorrects.length; i++) {
        incorrects[i].addEventListener('click', function () {
            incorrects[i].style.backgroundColor = 'red';
            document.querySelector('#feedback').innerHTML = 'inCorrect!';
        });
    }

    document.querySelector('#check').addEventListener('click', function () {
        let inp = document.querySelector('#inp');
        if (inp.value == 'deutschland') {
            inp.style.backgroundColor = 'green';
            document.querySelector('#feedback2').innerHTML = 'Correct!';
        } else {
            inp.style.backgroundColor = 'red';
            document.querySelector('#feedback2').innerHTML = 'inCorrect!';
        }
    });


});
    