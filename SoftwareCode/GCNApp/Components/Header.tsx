import React from 'react';
import {StyleSheet, Text, TouchableOpacity, View} from 'react-native';
import {firebaseAuth} from '../FirebaseConfig';

export default function Header() {
  return (
    <View style={styles.topView}>
      <Text style={styles.headerText}>GeoNav Application</Text>
      <TouchableOpacity
        style={styles.logoutButton}
        onPress={() => {
          firebaseAuth.signOut();
        }}>
        <Text style={styles.logoutText}>Logout</Text>
      </TouchableOpacity>
    </View>
  );
}

const styles = StyleSheet.create({
  containerStyle: {
    backgroundColor: 'white',
    height: '100%',
    display: 'flex',
    alignItems: 'center',
    //justifyContent: 'center',
  },
  topView: {
    display: 'flex',
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-between',
    marginBottom: 5,
    borderBottomWidth: 2,
    padding: 10,
  },
  headerText: {
    fontWeight: 'bold',
    fontSize: 20,
    marginBottom: 5,
  },
  logoutButton: {
    backgroundColor: 'red',
    padding: 5,
    borderRadius: 5,
  },
  logoutText: {
    color: 'white',
  },
});
