/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 */

import React, {useEffect, useState} from 'react';
import {NavigationContainer} from '@react-navigation/native';
import {createNativeStackNavigator} from '@react-navigation/native-stack';
import Login from './Pages/Login';
import HomePage from './Pages/HomePage';
import {User, onAuthStateChanged} from 'firebase/auth';
import {firebaseAuth} from './FirebaseConfig';

function App(): JSX.Element {
  const Stack = createNativeStackNavigator();
  const [user, setUser] = useState<User | null>(null);
  const [isAdmin, setIsAdmin] = useState(false);
  const adminAccess = ['admin@gmail.com'];

  useEffect(() => {
    onAuthStateChanged(firebaseAuth, user => {
      console.log(user);
      setUser(user);
    });
  });
  if (user?.email) {
    if (user.email in adminAccess) {
      setIsAdmin(true);
    }
  }

  return (
    <NavigationContainer>
      <Stack.Navigator initialRouteName="Login">
        {user ? (
          <Stack.Screen
            name="HomePage"
            component={HomePage}
            initialParams={{isAdmin: isAdmin}}
            options={{headerShown: false}}
          />
        ) : (
          <Stack.Screen
            name="Login"
            component={Login}
            options={{headerShown: false}}
          />
        )}
      </Stack.Navigator>
    </NavigationContainer>
  );
}

export default App;
