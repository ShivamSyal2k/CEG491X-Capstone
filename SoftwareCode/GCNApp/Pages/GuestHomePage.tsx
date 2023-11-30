import React from 'react';
import {SafeAreaView, StyleSheet, Text, View} from 'react-native';

export default function GuestHomePage() {
  return (
    <SafeAreaView style={{display: 'flex', alignItems: 'center'}}>
      <View style={styles.informationPanel}>
        <Text style={styles.headerText}>Information Panel</Text>
        <Text>Temperature: 20 degrees</Text>
        <Text>Status: OKAY</Text>
      </View>
      <View style={styles.containerStyle}>
        <Text style={styles.headerText}>Video Feed</Text>
        <View style={styles.videoView}>
          <Text style={{color: 'white'}}>.</Text>
        </View>
        <Text>View Only mode</Text>
      </View>
    </SafeAreaView>
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
    alignItems: 'center',
    justifyContent: 'center',
    marginBottom: 5,
    borderBottomWidth: 2,
  },
  headerText: {
    fontWeight: 'bold',
    fontSize: 20,
    marginBottom: 5,
  },
  videoView: {
    borderColor: 'black',
    borderWidth: 2,
    height: 250,
    width: 420,
    backgroundColor: 'black',
  },
  buttonView: {
    height: 150,
    width: 'auto',
    marginTop: 10,
    display: 'flex',
    alignItems: 'center',
    padding: 20,
  },
  lowerButtonView: {
    display: 'flex',
    justifyContent: 'space-around',
    flexDirection: 'row',
  },
  informationPanel: {
    borderWidth: 2,
    borderColor: 'black',
    width: '97%',
    margin: 15,
    marginBottom: 30,
    borderRadius: 10,
    padding: 10,
  },
  controlButtons: {
    margin: 5,
    borderWidth: 2,
    padding: 10,
    backgroundColor: 'lightblue',
  },
});
