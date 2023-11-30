// Import the functions you need from the SDKs you need
import {initializeApp} from 'firebase/app';
import {getAuth} from 'firebase/auth';
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: 'AIzaSyCVvRLi713rEpc8CfRR2UtRqzzn--drHY0',
  authDomain: 'gcnapplication-e5c9d.firebaseapp.com',
  projectId: 'gcnapplication-e5c9d',
  storageBucket: 'gcnapplication-e5c9d.appspot.com',
  messagingSenderId: '1000946373447',
  appId: '1:1000946373447:web:e1e305f01feab60ca93262',
  measurementId: 'G-349K49N8PC',
};

// Initialize Firebase
export const firebaseApp = initializeApp(firebaseConfig);
export const firebaseAuth = getAuth(firebaseApp);
