<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-calendar"></i> 账户安全设置 </el-breadcrumb-item>
                <el-breadcrumb-item>账户冻结状态</el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container"> 
            <div class="form-box">
                <el-form ref="form" :model="form"  label-width="280px" class="box-content">
                    <!-- <span class="span-text">账号冻结状态:</span> -->
                    <div class="tag-group">
                        <span class="tag-group_title">账号冻结状态:</span>
                        <el-tag v-if="accountFlag">正常</el-tag>
                        <el-tag v-else type="danger">冻结</el-tag>
                    </div>
                </el-form>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    inject: ['reload'],
    name: 'accountStatus',
    data() {
        return {
            form: {
            },
            accountFlag:false,
        };
    },
    //  或者使用做个地址请求 '/api/student/findStudentByID?id=1'
    created() {
           if(this.$store.getters.getUser.status =='0'){
               this.accountFlag=false;
           }else{
                this.accountFlag=true;
           }
    },
    methods: {
    }
};
</script>

<style scoped>
.container {
    position: relative;
    width: 100%;
    height: 100%;
    padding: 30px 30px 250px;
}
.onChange {
    position: absolute;
    right: -50px;
}

.tag-group {
    font-size: 20px;
    text-align: center;
    line-height: 18px;
    padding: 50px 200px;
}
.tag-tag {
    position: relative;
}
</style>