const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');
const card = require('../models/card_model');

router.post('/', function (req, res) {
  if (!req.body.cardnumber || !req.body.pin) {
    console.log('username or password missing');
    res.send(401);
    return;
  }
  const cardnum = req.body.cardnumber;
  const pin = req.body.pin;

  card.checkPassword(cardnum, (dbError, dbResult) => {
    if (dbError) {
      res.send(500);
      return;
    }
    if (!dbResult.length) {
      res.send(`Card number doesn't exist`);
      return;
    }
    if (dbResult[0].locked_status >= 3) {
      res.status(403).send(`Card locked.`);
    }
    console.log('hei', dbResult);
    bcrypt.compare(pin, dbResult[0].pin, (err, compareResult) => {
      if (compareResult) {
        const token = generateAccessToken({ cardnumber: cardnum });
        card.setLockedStatus(
          {
            cardnum,
            locked_status: 0,
          },
          (dbError, _dbResult) => {
            // Login was successful, if resetting counter fails => only log error
            if (dbError) console.log(`Error resetting locked_status`);
          },
        );
        res.send({ token });
      } else {
        console.log('login failed');
        card.setLockedStatus(
          {
            cardnum,
            locked_status: dbResult[0].locked_status + 1,
          },
          (dbError, dbResult) => {
            console.log(dbError);
            res.sendStatus(401);
          },
        );
      }
    });
  });
});

function generateAccessToken(cardnumber) {
  dotenv.config();
  return jwt.sign(cardnumber, process.env.JWT_TOKEN, { expiresIn: '1800s' });
}

module.exports = router;
