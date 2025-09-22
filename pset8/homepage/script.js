document.addEventListener('DOMContentLoaded', function(){

    let score = 0;

            let correct = document.querySelectorAll('.c');

                for(let j = 0; j < correct.length; j++)
                {
                    correct[j].addEventListener('click', function(){
                    correct[j].style.backgroundColor = 'Green';
                    score++;
                    if (score == 5)
                    {
                        alert("all correct!");
                        score = 0;
                    }
                    });
                }

            let incorrect =  document.querySelectorAll('.i');

                for(let i = 0; i < incorrect.length; i++)
                {
                    incorrect[i].addEventListener('click', function(){
                    incorrect[i].style.backgroundColor = 'Red';
                    });
                }
            });
