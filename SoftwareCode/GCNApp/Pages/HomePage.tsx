import React from 'react';
import {SafeAreaView} from 'react-native';
import Header from '../Components/Header';
import GuestHomePage from './GuestHomePage';
import AdminHomePage from './AdminHomePage';

export interface HomePageProps {
  isAdmin: Boolean;
}
export default function HomePage() {
  return (
    <SafeAreaView>
      <Header />
      {false ? <AdminHomePage /> : <GuestHomePage />}
    </SafeAreaView>
  );
}
