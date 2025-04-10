import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";

const firebaseConfig = {
    apiKey: "AIzaSyCiLX81O5YZVrhrkzRr8jgephcNFbbgAGY",
    authDomain: "monitortemp-2b4ff.firebaseapp.com",
    projectId: "monitortemp-2b4ff",
    storageBucket: "monitortemp-2b4ff.firebasestorage.app",
    messagingSenderId: "325217332868",
    appId: "1:325217332868:web:1e934ed5b190eadf6fdcd1",
    measurementId: "G-DTZJNBDV90"
};

const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);

const tempRef = ref(db, "dados/temperatura");
const umiRef = ref(db, "dados/umidade");

const ledImg = document.getElementById("ledDinamico");

onValue(tempRef, (snapshot) => {
  const temp = snapshot.val();
  console.log("Temperatura:", temp);

  if (temp >= 30) {
    ledImg.src = "img/redled.png";
  } else {
    ledImg.src = "img/greenled.png";
  }
});

onValue(umiRef, (snapshot) => {
  const umi = snapshot.val();
  console.log("Umidade:", umi);
});
