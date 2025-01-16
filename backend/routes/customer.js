const express = require('express');
const router = express.Router();
const customer = require('../models/customer_model');

  router.get('/',function(request, response){
    customer.getAll(function(err, result){
        if(err){
           response.json(err);
        }
        else {
            response.json(result);
        }
    })
  });

  router.get('/:idcustomer',function(request, response){
    customer.getById(request.params.idcustomer, function(err, result){
        if(err){
           response.json(err);
        }
        else {
            response.json(result[0]);
        }
    })
  });

  router.post('/',function(request, response){
    customer.add(request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

router.put('/:idcustomer',function(request, response){
    customer.update(request.params.idcustomer,request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:idcustomer',function(request, response){
    customer.delete(request.params.idcustomer, function(err,result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }  
    })
});


module.exports = router;

