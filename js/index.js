function atualizarLed() {
    fetch('/temperatura')
      .then(response => response.json())
      .then(data => {
        const temperatura = data.temp;
        const ledImg = document.querySelector('.rocket');

        if (temperatura >= 30) {
          ledImg.src = 'img/redled.png';
        } else {
          ledImg.src = 'img/greenled.png';
        }
      })
      .catch(err => console.error('Erro ao buscar temperatura:', err));
  }